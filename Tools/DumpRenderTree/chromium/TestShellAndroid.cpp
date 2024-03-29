/*
 * Copyright (C) 2012 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "TestShell.h"

#include <android/log.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <wtf/Assertions.h>

namespace {

const char optionInFIFO[] = "--in-fifo=";
const char optionOutFIFO[] = "--out-fifo=";
const char optionErrFile[] = "--err-file=";

void androidLogError(const char* format, ...) WTF_ATTRIBUTE_PRINTF(1, 2);

void androidLogError(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    __android_log_vprint(ANDROID_LOG_ERROR, "DumpRenderTree", format, args);
    va_end(args);
}

void removeArg(int index, int* argc, char*** argv)
{
    for (int i = index; i < *argc; ++i)
        (*argv)[i] = (*argv)[i + 1];
    --*argc;
}

void createFIFO(const char* fifoPath)
{
    unlink(fifoPath);
    if (mkfifo(fifoPath, 0600)) {
        androidLogError("Failed to create fifo %s: %s\n", fifoPath, strerror(errno));
        exit(EXIT_FAILURE);
    }
}

void createFile(const char* filePath)
{
    unlink(filePath);
    int fd = creat(filePath, 0600);
    if (fd < 0) {
        androidLogError("Failed to create file %s: %s\n", filePath, strerror(errno));
        exit(EXIT_FAILURE);
    }
    close(fd);
}

void redirectToFile(FILE* stream, const char* path, const char* mode)
{
    if (!freopen(path, mode, stream)) {
        androidLogError("Failed to redirect stream to file: %s: %s\n", path, strerror(errno));
        exit(EXIT_FAILURE);
    }
}

} // namespace

void platformInit(int* argc, char*** argv)
{
    const char* inFIFO = 0;
    const char* outFIFO = 0;
    const char* errFile = 0;
    for (int i = 1; i < *argc; ) {
        const char* argument = (*argv)[i];
        if (strstr(argument, optionInFIFO) == argument) {
            inFIFO = argument + WTF_ARRAY_LENGTH(optionInFIFO) - 1;
            createFIFO(inFIFO);
            removeArg(i, argc, argv);
        } else if (strstr(argument, optionOutFIFO) == argument) {
            outFIFO = argument + WTF_ARRAY_LENGTH(optionOutFIFO) - 1;
            createFIFO(outFIFO);
            removeArg(i, argc, argv);
        } else if (strstr(argument, optionErrFile) == argument) {
            errFile = argument + WTF_ARRAY_LENGTH(optionErrFile) - 1;
            createFile(errFile);
            removeArg(i, argc, argv);
        } else
            ++i;
    }

    // The order of createFIFO() and redirectToFIFO() is important to avoid deadlock.
    if (outFIFO)
        redirectToFile(stdout, outFIFO, "w");
    if (inFIFO)
        redirectToFile(stdin, inFIFO, "r");
    if (errFile)
        redirectToFile(stderr, errFile, "w");
    else {
        // Redirect stderr to stdout.
        dup2(1, 2);
    }
}
