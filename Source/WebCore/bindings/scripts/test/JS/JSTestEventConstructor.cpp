/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"
#include "JSTestEventConstructor.h"

#include "JSDictionary.h"
#include "KURL.h"
#include "TestEventConstructor.h"
#include <runtime/Error.h>
#include <runtime/JSString.h>
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSTestEventConstructor);
/* Hash table for constructor */

static const HashTableValue JSTestEventConstructorTableValues[] =
{
    { "attr1", DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestEventConstructorAttr1), (intptr_t)0, NoIntrinsic },
    { "attr2", DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestEventConstructorAttr2), (intptr_t)0, NoIntrinsic },
    { "constructor", DontEnum | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestEventConstructorConstructor), (intptr_t)0, NoIntrinsic },
    { 0, 0, 0, 0, NoIntrinsic }
};

static const HashTable JSTestEventConstructorTable = { 9, 7, JSTestEventConstructorTableValues, 0 };
/* Hash table for constructor */

static const HashTableValue JSTestEventConstructorConstructorTableValues[] =
{
    { 0, 0, 0, 0, NoIntrinsic }
};

static const HashTable JSTestEventConstructorConstructorTable = { 1, 0, JSTestEventConstructorConstructorTableValues, 0 };
const ClassInfo JSTestEventConstructorConstructor::s_info = { "TestEventConstructorConstructor", &Base::s_info, &JSTestEventConstructorConstructorTable, 0, CREATE_METHOD_TABLE(JSTestEventConstructorConstructor) };

JSTestEventConstructorConstructor::JSTestEventConstructorConstructor(Structure* structure, JSDOMGlobalObject* globalObject)
    : DOMConstructorObject(structure, globalObject)
{
}

void JSTestEventConstructorConstructor::finishCreation(ExecState* exec, JSDOMGlobalObject* globalObject)
{
    Base::finishCreation(exec->globalData());
    ASSERT(inherits(&s_info));
    putDirect(exec->globalData(), exec->propertyNames().prototype, JSTestEventConstructorPrototype::self(exec, globalObject), DontDelete | ReadOnly);
    putDirect(exec->globalData(), exec->propertyNames().length, jsNumber(2), ReadOnly | DontDelete | DontEnum);
}

bool JSTestEventConstructorConstructor::getOwnPropertySlot(JSCell* cell, ExecState* exec, PropertyName propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSTestEventConstructorConstructor, JSDOMWrapper>(exec, &JSTestEventConstructorConstructorTable, jsCast<JSTestEventConstructorConstructor*>(cell), propertyName, slot);
}

bool JSTestEventConstructorConstructor::getOwnPropertyDescriptor(JSObject* object, ExecState* exec, PropertyName propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSTestEventConstructorConstructor, JSDOMWrapper>(exec, &JSTestEventConstructorConstructorTable, jsCast<JSTestEventConstructorConstructor*>(object), propertyName, descriptor);
}

EncodedJSValue JSC_HOST_CALL JSTestEventConstructorConstructor::constructJSTestEventConstructor(ExecState* exec)
{
    JSTestEventConstructorConstructor* jsConstructor = jsCast<JSTestEventConstructorConstructor*>(exec->callee());

    ScriptExecutionContext* executionContext = jsConstructor->scriptExecutionContext();
    if (!executionContext)
        return throwVMError(exec, createReferenceError(exec, "Constructor associated execution context is unavailable"));

    AtomicString eventType = ustringToAtomicString(exec->argument(0).toString(exec)->value(exec));
    if (exec->hadException())
        return JSValue::encode(jsUndefined());

    TestEventConstructorInit eventInit;

    JSValue initializerValue = exec->argument(1);
    if (!initializerValue.isUndefinedOrNull()) {
        // Given the above test, this will always yield an object.
        JSObject* initializerObject = initializerValue.toObject(exec);

        // Create the dictionary wrapper from the initializer object.
        JSDictionary dictionary(exec, initializerObject);

        // Attempt to fill in the EventInit.
        if (!fillTestEventConstructorInit(eventInit, dictionary))
            return JSValue::encode(jsUndefined());
    }

    RefPtr<TestEventConstructor> event = TestEventConstructor::create(eventType, eventInit);
    return JSValue::encode(toJS(exec, jsConstructor->globalObject(), event.get()));
}

bool fillTestEventConstructorInit(TestEventConstructorInit& eventInit, JSDictionary& dictionary)
{
    if (!dictionary.tryGetProperty("attr2", eventInit.attr2))
        return false;
    return true;
}

ConstructType JSTestEventConstructorConstructor::getConstructData(JSCell*, ConstructData& constructData)
{
    constructData.native.function = constructJSTestEventConstructor;
    return ConstructTypeHost;
}

/* Hash table for prototype */

static const HashTableValue JSTestEventConstructorPrototypeTableValues[] =
{
    { 0, 0, 0, 0, NoIntrinsic }
};

static const HashTable JSTestEventConstructorPrototypeTable = { 1, 0, JSTestEventConstructorPrototypeTableValues, 0 };
const ClassInfo JSTestEventConstructorPrototype::s_info = { "TestEventConstructorPrototype", &Base::s_info, &JSTestEventConstructorPrototypeTable, 0, CREATE_METHOD_TABLE(JSTestEventConstructorPrototype) };

JSObject* JSTestEventConstructorPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSTestEventConstructor>(exec, globalObject);
}

const ClassInfo JSTestEventConstructor::s_info = { "TestEventConstructor", &Base::s_info, &JSTestEventConstructorTable, 0 , CREATE_METHOD_TABLE(JSTestEventConstructor) };

JSTestEventConstructor::JSTestEventConstructor(Structure* structure, JSDOMGlobalObject* globalObject, PassRefPtr<TestEventConstructor> impl)
    : JSDOMWrapper(structure, globalObject)
    , m_impl(impl.leakRef())
{
}

void JSTestEventConstructor::finishCreation(JSGlobalData& globalData)
{
    Base::finishCreation(globalData);
    ASSERT(inherits(&s_info));
}

JSObject* JSTestEventConstructor::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return JSTestEventConstructorPrototype::create(exec->globalData(), globalObject, JSTestEventConstructorPrototype::createStructure(globalObject->globalData(), globalObject, globalObject->objectPrototype()));
}

void JSTestEventConstructor::destroy(JSC::JSCell* cell)
{
    JSTestEventConstructor* thisObject = static_cast<JSTestEventConstructor*>(cell);
    thisObject->JSTestEventConstructor::~JSTestEventConstructor();
}

JSTestEventConstructor::~JSTestEventConstructor()
{
    releaseImplIfNotNull();
}

bool JSTestEventConstructor::getOwnPropertySlot(JSCell* cell, ExecState* exec, PropertyName propertyName, PropertySlot& slot)
{
    JSTestEventConstructor* thisObject = jsCast<JSTestEventConstructor*>(cell);
    ASSERT_GC_OBJECT_INHERITS(thisObject, &s_info);
    return getStaticValueSlot<JSTestEventConstructor, Base>(exec, &JSTestEventConstructorTable, thisObject, propertyName, slot);
}

bool JSTestEventConstructor::getOwnPropertyDescriptor(JSObject* object, ExecState* exec, PropertyName propertyName, PropertyDescriptor& descriptor)
{
    JSTestEventConstructor* thisObject = jsCast<JSTestEventConstructor*>(object);
    ASSERT_GC_OBJECT_INHERITS(thisObject, &s_info);
    return getStaticValueDescriptor<JSTestEventConstructor, Base>(exec, &JSTestEventConstructorTable, thisObject, propertyName, descriptor);
}

JSValue jsTestEventConstructorAttr1(ExecState* exec, JSValue slotBase, PropertyName)
{
    JSTestEventConstructor* castedThis = jsCast<JSTestEventConstructor*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TestEventConstructor* impl = static_cast<TestEventConstructor*>(castedThis->impl());
    JSValue result = jsString(exec, impl->attr1());
    return result;
}


JSValue jsTestEventConstructorAttr2(ExecState* exec, JSValue slotBase, PropertyName)
{
    JSTestEventConstructor* castedThis = jsCast<JSTestEventConstructor*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    TestEventConstructor* impl = static_cast<TestEventConstructor*>(castedThis->impl());
    JSValue result = jsString(exec, impl->attr2());
    return result;
}


JSValue jsTestEventConstructorConstructor(ExecState* exec, JSValue slotBase, PropertyName)
{
    JSTestEventConstructor* domObject = jsCast<JSTestEventConstructor*>(asObject(slotBase));
    return JSTestEventConstructor::getConstructor(exec, domObject->globalObject());
}

JSValue JSTestEventConstructor::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTestEventConstructorConstructor>(exec, jsCast<JSDOMGlobalObject*>(globalObject));
}

static inline bool isObservable(JSTestEventConstructor* jsTestEventConstructor)
{
    if (jsTestEventConstructor->hasCustomProperties())
        return true;
    return false;
}

bool JSTestEventConstructorOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, SlotVisitor& visitor)
{
    JSTestEventConstructor* jsTestEventConstructor = jsCast<JSTestEventConstructor*>(handle.get().asCell());
    if (!isObservable(jsTestEventConstructor))
        return false;
    UNUSED_PARAM(visitor);
    return false;
}

void JSTestEventConstructorOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    JSTestEventConstructor* jsTestEventConstructor = jsCast<JSTestEventConstructor*>(handle.get().asCell());
    DOMWrapperWorld* world = static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, jsTestEventConstructor->impl(), jsTestEventConstructor);
    jsTestEventConstructor->releaseImpl();
}

JSC::JSValue toJS(JSC::ExecState* exec, JSDOMGlobalObject* globalObject, TestEventConstructor* impl)
{
    return wrap<JSTestEventConstructor>(exec, globalObject, impl);
}

TestEventConstructor* toTestEventConstructor(JSC::JSValue value)
{
    return value.inherits(&JSTestEventConstructor::s_info) ? jsCast<JSTestEventConstructor*>(asObject(value))->impl() : 0;
}

}
