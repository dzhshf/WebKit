/*
 *  Copyright (C) 1999-2000 Harri Porten (porten@kde.org)
 *  Copyright (C) 2003, 2006, 2007, 2008, 2009 Apple Inc. All rights reserved.
 *  Copyright (C) 2007 Cameron Zwarich (cwzwarich@uwaterloo.ca)
 *  Copyright (C) 2007 Maks Orlovich
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this library; see the file COPYING.LIB.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 *
 */

#ifndef JSFunction_h
#define JSFunction_h

#include "InternalFunction.h"
#include "JSObject.h"

namespace JSC {

    class ExecutableBase;
    class FunctionExecutable;
    class FunctionPrototype;
    class JSActivation;
    class JSGlobalObject;
    class LLIntOffsetsExtractor;
    class NativeExecutable;
    class SourceCode;
    namespace DFG {
    class SpeculativeJIT;
    class JITCompiler;
    }

    JS_EXPORT_PRIVATE EncodedJSValue JSC_HOST_CALL callHostFunctionAsConstructor(ExecState*);

    JS_EXPORT_PRIVATE UString getCalculatedDisplayName(CallFrame*, JSObject*);
    
    class JSFunction : public JSNonFinalObject {
        friend class JIT;
        friend class DFG::SpeculativeJIT;
        friend class DFG::JITCompiler;
        friend class JSGlobalData;

    public:
        typedef JSNonFinalObject Base;

        JS_EXPORT_PRIVATE static JSFunction* create(ExecState*, JSGlobalObject*, int length, const UString& name, NativeFunction, Intrinsic = NoIntrinsic, NativeFunction nativeConstructor = callHostFunctionAsConstructor);

        static JSFunction* create(ExecState* exec, FunctionExecutable* executable, ScopeChainNode* scopeChain)
        {
            JSFunction* function = new (NotNull, allocateCell<JSFunction>(*exec->heap())) JSFunction(exec, executable, scopeChain);
            ASSERT(function->structure()->globalObject());
            function->finishCreation(exec, executable, scopeChain);
            return function;
        }
        
        JS_EXPORT_PRIVATE const UString& name(ExecState*);
        JS_EXPORT_PRIVATE const UString displayName(ExecState*);
        const UString calculatedDisplayName(ExecState*);

        ScopeChainNode* scope()
        {
            ASSERT(!isHostFunctionNonInline());
            return m_scopeChain.get();
        }
        // This method may be called for host functins, in which case it
        // will return an arbitrary value. This should only be used for
        // optimized paths in which the return value does not matter for
        // host functions, and checking whether the function is a host
        // function is deemed too expensive.
        ScopeChainNode* scopeUnchecked()
        {
            return m_scopeChain.get();
        }
        void setScope(JSGlobalData& globalData, ScopeChainNode* scopeChain)
        {
            ASSERT(!isHostFunctionNonInline());
            m_scopeChain.set(globalData, this, scopeChain);
        }

        ExecutableBase* executable() const { return m_executable.get(); }

        // To call either of these methods include Executable.h
        inline bool isHostFunction() const;
        FunctionExecutable* jsExecutable() const;

        JS_EXPORT_PRIVATE const SourceCode* sourceCode() const;

        static JS_EXPORTDATA const ClassInfo s_info;

        static Structure* createStructure(JSGlobalData& globalData, JSGlobalObject* globalObject, JSValue prototype) 
        {
            ASSERT(globalObject);
            return Structure::create(globalData, globalObject, prototype, TypeInfo(JSFunctionType, StructureFlags), &s_info); 
        }

        NativeFunction nativeFunction();
        NativeFunction nativeConstructor();

        static ConstructType getConstructData(JSCell*, ConstructData&);
        static CallType getCallData(JSCell*, CallData&);

        static inline size_t offsetOfScopeChain()
        {
            return OBJECT_OFFSETOF(JSFunction, m_scopeChain);
        }

        static inline size_t offsetOfExecutable()
        {
            return OBJECT_OFFSETOF(JSFunction, m_executable);
        }

        Structure* cachedInheritorID(ExecState* exec)
        {
            if (UNLIKELY(!m_cachedInheritorID))
                return cacheInheritorID(exec);
            return m_cachedInheritorID.get();
        }

        static size_t offsetOfCachedInheritorID()
        {
            return OBJECT_OFFSETOF(JSFunction, m_cachedInheritorID);
        }

    protected:
        const static unsigned StructureFlags = OverridesGetOwnPropertySlot | ImplementsHasInstance | OverridesVisitChildren | OverridesGetPropertyNames | JSObject::StructureFlags;

        JS_EXPORT_PRIVATE JSFunction(ExecState*, JSGlobalObject*, Structure*);
        JSFunction(ExecState*, FunctionExecutable*, ScopeChainNode*);
        
        void finishCreation(ExecState*, NativeExecutable*, int length, const UString& name);
        void finishCreation(ExecState*, FunctionExecutable*, ScopeChainNode*);

        Structure* cacheInheritorID(ExecState*);

        static bool getOwnPropertySlot(JSCell*, ExecState*, PropertyName, PropertySlot&);
        static bool getOwnPropertyDescriptor(JSObject*, ExecState*, PropertyName, PropertyDescriptor&);
        static void getOwnPropertyNames(JSObject*, ExecState*, PropertyNameArray&, EnumerationMode = ExcludeDontEnumProperties);
        static bool defineOwnProperty(JSObject*, ExecState*, PropertyName, PropertyDescriptor&, bool shouldThrow);

        static void put(JSCell*, ExecState*, PropertyName, JSValue, PutPropertySlot&);

        static bool deleteProperty(JSCell*, ExecState*, PropertyName);

        static void visitChildren(JSCell*, SlotVisitor&);

    private:
        friend class LLIntOffsetsExtractor;
        
        JS_EXPORT_PRIVATE bool isHostFunctionNonInline() const;

        static JSValue argumentsGetter(ExecState*, JSValue, PropertyName);
        static JSValue callerGetter(ExecState*, JSValue, PropertyName);
        static JSValue lengthGetter(ExecState*, JSValue, PropertyName);

        WriteBarrier<ExecutableBase> m_executable;
        WriteBarrier<ScopeChainNode> m_scopeChain;
        WriteBarrier<Structure> m_cachedInheritorID;
    };

    inline bool JSValue::isFunction() const
    {
        return isCell() && (asCell()->inherits(&JSFunction::s_info) || asCell()->inherits(&InternalFunction::s_info));
    }

} // namespace JSC

#endif // JSFunction_h
