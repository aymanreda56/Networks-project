//
// Generated file, do not edit! Created by opp_msgtool 6.0 from CoordinatorMsg.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "CoordinatorMsg_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

CoordinatorMsg_Base::CoordinatorMsg_Base(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

CoordinatorMsg_Base::CoordinatorMsg_Base(const CoordinatorMsg_Base& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

CoordinatorMsg_Base::~CoordinatorMsg_Base()
{
}

CoordinatorMsg_Base& CoordinatorMsg_Base::operator=(const CoordinatorMsg_Base& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void CoordinatorMsg_Base::copy(const CoordinatorMsg_Base& other)
{
    this->Mtype = other.Mtype;
    this->startTime = other.startTime;
    this->startingNode = other.startingNode;
}

void CoordinatorMsg_Base::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->Mtype);
    doParsimPacking(b,this->startTime);
    doParsimPacking(b,this->startingNode);
}

void CoordinatorMsg_Base::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->Mtype);
    doParsimUnpacking(b,this->startTime);
    doParsimUnpacking(b,this->startingNode);
}

const char * CoordinatorMsg_Base::getMtype() const
{
    return this->Mtype.c_str();
}

void CoordinatorMsg_Base::setMtype(const char * Mtype)
{
    this->Mtype = Mtype;
}

int CoordinatorMsg_Base::getStartTime() const
{
    return this->startTime;
}

void CoordinatorMsg_Base::setStartTime(int startTime)
{
    this->startTime = startTime;
}

int CoordinatorMsg_Base::getStartingNode() const
{
    return this->startingNode;
}

void CoordinatorMsg_Base::setStartingNode(int startingNode)
{
    this->startingNode = startingNode;
}

class CoordinatorMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_Mtype,
        FIELD_startTime,
        FIELD_startingNode,
    };
  public:
    CoordinatorMsgDescriptor();
    virtual ~CoordinatorMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(CoordinatorMsgDescriptor)

CoordinatorMsgDescriptor::CoordinatorMsgDescriptor() : omnetpp::cClassDescriptor("CoordinatorMsg", "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

CoordinatorMsgDescriptor::~CoordinatorMsgDescriptor()
{
    delete[] propertyNames;
}

bool CoordinatorMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CoordinatorMsg_Base *>(obj)!=nullptr;
}

const char **CoordinatorMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "customize",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *CoordinatorMsgDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "customize")) return "true";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int CoordinatorMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int CoordinatorMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_Mtype
        FD_ISEDITABLE,    // FIELD_startTime
        FD_ISEDITABLE,    // FIELD_startingNode
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *CoordinatorMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "Mtype",
        "startTime",
        "startingNode",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int CoordinatorMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "Mtype") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "startTime") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "startingNode") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *CoordinatorMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_Mtype
        "int",    // FIELD_startTime
        "int",    // FIELD_startingNode
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **CoordinatorMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *CoordinatorMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int CoordinatorMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    CoordinatorMsg_Base *pp = omnetpp::fromAnyPtr<CoordinatorMsg_Base>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void CoordinatorMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    CoordinatorMsg_Base *pp = omnetpp::fromAnyPtr<CoordinatorMsg_Base>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'CoordinatorMsg_Base'", field);
    }
}

const char *CoordinatorMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    CoordinatorMsg_Base *pp = omnetpp::fromAnyPtr<CoordinatorMsg_Base>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CoordinatorMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    CoordinatorMsg_Base *pp = omnetpp::fromAnyPtr<CoordinatorMsg_Base>(object); (void)pp;
    switch (field) {
        case FIELD_Mtype: return oppstring2string(pp->getMtype());
        case FIELD_startTime: return long2string(pp->getStartTime());
        case FIELD_startingNode: return long2string(pp->getStartingNode());
        default: return "";
    }
}

void CoordinatorMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CoordinatorMsg_Base *pp = omnetpp::fromAnyPtr<CoordinatorMsg_Base>(object); (void)pp;
    switch (field) {
        case FIELD_Mtype: pp->setMtype((value)); break;
        case FIELD_startTime: pp->setStartTime(string2long(value)); break;
        case FIELD_startingNode: pp->setStartingNode(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CoordinatorMsg_Base'", field);
    }
}

omnetpp::cValue CoordinatorMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    CoordinatorMsg_Base *pp = omnetpp::fromAnyPtr<CoordinatorMsg_Base>(object); (void)pp;
    switch (field) {
        case FIELD_Mtype: return pp->getMtype();
        case FIELD_startTime: return pp->getStartTime();
        case FIELD_startingNode: return pp->getStartingNode();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'CoordinatorMsg_Base' as cValue -- field index out of range?", field);
    }
}

void CoordinatorMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CoordinatorMsg_Base *pp = omnetpp::fromAnyPtr<CoordinatorMsg_Base>(object); (void)pp;
    switch (field) {
        case FIELD_Mtype: pp->setMtype(value.stringValue()); break;
        case FIELD_startTime: pp->setStartTime(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_startingNode: pp->setStartingNode(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CoordinatorMsg_Base'", field);
    }
}

const char *CoordinatorMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr CoordinatorMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    CoordinatorMsg_Base *pp = omnetpp::fromAnyPtr<CoordinatorMsg_Base>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void CoordinatorMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    CoordinatorMsg_Base *pp = omnetpp::fromAnyPtr<CoordinatorMsg_Base>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CoordinatorMsg_Base'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

