//
// Generated file, do not edit! Created by opp_msgtool 6.0 from NodeMsg.msg.
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
#include "NodeMsg_m.h"

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

Register_Class(NodeMsg)

NodeMsg::NodeMsg(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

NodeMsg::NodeMsg(const NodeMsg& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

NodeMsg::~NodeMsg()
{
}

NodeMsg& NodeMsg::operator=(const NodeMsg& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void NodeMsg::copy(const NodeMsg& other)
{
    this->seq_num = other.seq_num;
    this->payload = other.payload;
    this->parityByte = other.parityByte;
    this->messageType = other.messageType;
    this->ack_num = other.ack_num;
}

void NodeMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->seq_num);
    doParsimPacking(b,this->payload);
    doParsimPacking(b,this->parityByte);
    doParsimPacking(b,this->messageType);
    doParsimPacking(b,this->ack_num);
}

void NodeMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->seq_num);
    doParsimUnpacking(b,this->payload);
    doParsimUnpacking(b,this->parityByte);
    doParsimUnpacking(b,this->messageType);
    doParsimUnpacking(b,this->ack_num);
}

int NodeMsg::getSeq_num() const
{
    return this->seq_num;
}

void NodeMsg::setSeq_num(int seq_num)
{
    this->seq_num = seq_num;
}

const char * NodeMsg::getPayload() const
{
    return this->payload.c_str();
}

void NodeMsg::setPayload(const char * payload)
{
    this->payload = payload;
}

char NodeMsg::getParityByte() const
{
    return this->parityByte;
}

void NodeMsg::setParityByte(char parityByte)
{
    this->parityByte = parityByte;
}

int NodeMsg::getMessageType() const
{
    return this->messageType;
}

void NodeMsg::setMessageType(int messageType)
{
    this->messageType = messageType;
}

int NodeMsg::getAck_num() const
{
    return this->ack_num;
}

void NodeMsg::setAck_num(int ack_num)
{
    this->ack_num = ack_num;
}

class NodeMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_seq_num,
        FIELD_payload,
        FIELD_parityByte,
        FIELD_messageType,
        FIELD_ack_num,
    };
  public:
    NodeMsgDescriptor();
    virtual ~NodeMsgDescriptor();

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

Register_ClassDescriptor(NodeMsgDescriptor)

NodeMsgDescriptor::NodeMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(NodeMsg)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

NodeMsgDescriptor::~NodeMsgDescriptor()
{
    delete[] propertyNames;
}

bool NodeMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NodeMsg *>(obj)!=nullptr;
}

const char **NodeMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *NodeMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int NodeMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int NodeMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_seq_num
        FD_ISEDITABLE,    // FIELD_payload
        FD_ISEDITABLE,    // FIELD_parityByte
        FD_ISEDITABLE,    // FIELD_messageType
        FD_ISEDITABLE,    // FIELD_ack_num
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *NodeMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "seq_num",
        "payload",
        "parityByte",
        "messageType",
        "ack_num",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int NodeMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "seq_num") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "payload") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "parityByte") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "messageType") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "ack_num") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *NodeMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_seq_num
        "string",    // FIELD_payload
        "char",    // FIELD_parityByte
        "int",    // FIELD_messageType
        "int",    // FIELD_ack_num
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **NodeMsgDescriptor::getFieldPropertyNames(int field) const
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

const char *NodeMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int NodeMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    NodeMsg *pp = omnetpp::fromAnyPtr<NodeMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void NodeMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    NodeMsg *pp = omnetpp::fromAnyPtr<NodeMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'NodeMsg'", field);
    }
}

const char *NodeMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    NodeMsg *pp = omnetpp::fromAnyPtr<NodeMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NodeMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    NodeMsg *pp = omnetpp::fromAnyPtr<NodeMsg>(object); (void)pp;
    switch (field) {
        case FIELD_seq_num: return long2string(pp->getSeq_num());
        case FIELD_payload: return oppstring2string(pp->getPayload());
        case FIELD_parityByte: return long2string(pp->getParityByte());
        case FIELD_messageType: return long2string(pp->getMessageType());
        case FIELD_ack_num: return long2string(pp->getAck_num());
        default: return "";
    }
}

void NodeMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    NodeMsg *pp = omnetpp::fromAnyPtr<NodeMsg>(object); (void)pp;
    switch (field) {
        case FIELD_seq_num: pp->setSeq_num(string2long(value)); break;
        case FIELD_payload: pp->setPayload((value)); break;
        case FIELD_parityByte: pp->setParityByte(string2long(value)); break;
        case FIELD_messageType: pp->setMessageType(string2long(value)); break;
        case FIELD_ack_num: pp->setAck_num(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'NodeMsg'", field);
    }
}

omnetpp::cValue NodeMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    NodeMsg *pp = omnetpp::fromAnyPtr<NodeMsg>(object); (void)pp;
    switch (field) {
        case FIELD_seq_num: return pp->getSeq_num();
        case FIELD_payload: return pp->getPayload();
        case FIELD_parityByte: return pp->getParityByte();
        case FIELD_messageType: return pp->getMessageType();
        case FIELD_ack_num: return pp->getAck_num();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'NodeMsg' as cValue -- field index out of range?", field);
    }
}

void NodeMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    NodeMsg *pp = omnetpp::fromAnyPtr<NodeMsg>(object); (void)pp;
    switch (field) {
        case FIELD_seq_num: pp->setSeq_num(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_payload: pp->setPayload(value.stringValue()); break;
        case FIELD_parityByte: pp->setParityByte(omnetpp::checked_int_cast<char>(value.intValue())); break;
        case FIELD_messageType: pp->setMessageType(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_ack_num: pp->setAck_num(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'NodeMsg'", field);
    }
}

const char *NodeMsgDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr NodeMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    NodeMsg *pp = omnetpp::fromAnyPtr<NodeMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void NodeMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    NodeMsg *pp = omnetpp::fromAnyPtr<NodeMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'NodeMsg'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

