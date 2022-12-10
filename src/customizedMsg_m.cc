//
// Generated file, do not edit! Created by opp_msgtool 6.0 from customizedMsg.msg.
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
#include "customizedMsg_m.h"

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

CustomizedMsg_Base::CustomizedMsg_Base(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

CustomizedMsg_Base::CustomizedMsg_Base(const CustomizedMsg_Base& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

CustomizedMsg_Base::~CustomizedMsg_Base()
{
}

CustomizedMsg_Base& CustomizedMsg_Base::operator=(const CustomizedMsg_Base& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void CustomizedMsg_Base::copy(const CustomizedMsg_Base& other)
{
    this->seq_num = other.seq_num;
    this->frame_type = other.frame_type;
    this->msg_payload = other.msg_payload;
    this->n_ack_value = other.n_ack_value;
    this->mycheckbits = other.mycheckbits;
}

void CustomizedMsg_Base::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->seq_num);
    doParsimPacking(b,this->frame_type);
    doParsimPacking(b,this->msg_payload);
    doParsimPacking(b,this->n_ack_value);
    doParsimPacking(b,this->mycheckbits);
}

void CustomizedMsg_Base::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->seq_num);
    doParsimUnpacking(b,this->frame_type);
    doParsimUnpacking(b,this->msg_payload);
    doParsimUnpacking(b,this->n_ack_value);
    doParsimUnpacking(b,this->mycheckbits);
}

int CustomizedMsg_Base::getSeq_num() const
{
    return this->seq_num;
}

void CustomizedMsg_Base::setSeq_num(int seq_num)
{
    this->seq_num = seq_num;
}

int CustomizedMsg_Base::getFrame_type() const
{
    return this->frame_type;
}

void CustomizedMsg_Base::setFrame_type(int frame_type)
{
    this->frame_type = frame_type;
}

const char * CustomizedMsg_Base::getMsg_payload() const
{
    return this->msg_payload.c_str();
}

void CustomizedMsg_Base::setMsg_payload(const char * msg_payload)
{
    this->msg_payload = msg_payload;
}

int CustomizedMsg_Base::getN_ack_value() const
{
    return this->n_ack_value;
}

void CustomizedMsg_Base::setN_ack_value(int n_ack_value)
{
    this->n_ack_value = n_ack_value;
}

char CustomizedMsg_Base::getMycheckbits() const
{
    return this->mycheckbits;
}

void CustomizedMsg_Base::setMycheckbits(char mycheckbits)
{
    this->mycheckbits = mycheckbits;
}

class CustomizedMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_seq_num,
        FIELD_frame_type,
        FIELD_msg_payload,
        FIELD_n_ack_value,
        FIELD_mycheckbits,
    };
  public:
    CustomizedMsgDescriptor();
    virtual ~CustomizedMsgDescriptor();

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

Register_ClassDescriptor(CustomizedMsgDescriptor)

CustomizedMsgDescriptor::CustomizedMsgDescriptor() : omnetpp::cClassDescriptor("CustomizedMsg", "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

CustomizedMsgDescriptor::~CustomizedMsgDescriptor()
{
    delete[] propertyNames;
}

bool CustomizedMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CustomizedMsg_Base *>(obj)!=nullptr;
}

const char **CustomizedMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "customize",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *CustomizedMsgDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "customize")) return "true";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int CustomizedMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int CustomizedMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_seq_num
        FD_ISEDITABLE,    // FIELD_frame_type
        FD_ISEDITABLE,    // FIELD_msg_payload
        FD_ISEDITABLE,    // FIELD_n_ack_value
        FD_ISEDITABLE,    // FIELD_mycheckbits
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *CustomizedMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "seq_num",
        "frame_type",
        "msg_payload",
        "n_ack_value",
        "mycheckbits",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int CustomizedMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "seq_num") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "frame_type") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "msg_payload") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "n_ack_value") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "mycheckbits") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *CustomizedMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_seq_num
        "int",    // FIELD_frame_type
        "string",    // FIELD_msg_payload
        "int",    // FIELD_n_ack_value
        "char",    // FIELD_mycheckbits
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **CustomizedMsgDescriptor::getFieldPropertyNames(int field) const
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

const char *CustomizedMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int CustomizedMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    CustomizedMsg_Base *pp = omnetpp::fromAnyPtr<CustomizedMsg_Base>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void CustomizedMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    CustomizedMsg_Base *pp = omnetpp::fromAnyPtr<CustomizedMsg_Base>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'CustomizedMsg_Base'", field);
    }
}

const char *CustomizedMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    CustomizedMsg_Base *pp = omnetpp::fromAnyPtr<CustomizedMsg_Base>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CustomizedMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    CustomizedMsg_Base *pp = omnetpp::fromAnyPtr<CustomizedMsg_Base>(object); (void)pp;
    switch (field) {
        case FIELD_seq_num: return long2string(pp->getSeq_num());
        case FIELD_frame_type: return long2string(pp->getFrame_type());
        case FIELD_msg_payload: return oppstring2string(pp->getMsg_payload());
        case FIELD_n_ack_value: return long2string(pp->getN_ack_value());
        case FIELD_mycheckbits: return long2string(pp->getMycheckbits());
        default: return "";
    }
}

void CustomizedMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CustomizedMsg_Base *pp = omnetpp::fromAnyPtr<CustomizedMsg_Base>(object); (void)pp;
    switch (field) {
        case FIELD_seq_num: pp->setSeq_num(string2long(value)); break;
        case FIELD_frame_type: pp->setFrame_type(string2long(value)); break;
        case FIELD_msg_payload: pp->setMsg_payload((value)); break;
        case FIELD_n_ack_value: pp->setN_ack_value(string2long(value)); break;
        case FIELD_mycheckbits: pp->setMycheckbits(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CustomizedMsg_Base'", field);
    }
}

omnetpp::cValue CustomizedMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    CustomizedMsg_Base *pp = omnetpp::fromAnyPtr<CustomizedMsg_Base>(object); (void)pp;
    switch (field) {
        case FIELD_seq_num: return pp->getSeq_num();
        case FIELD_frame_type: return pp->getFrame_type();
        case FIELD_msg_payload: return pp->getMsg_payload();
        case FIELD_n_ack_value: return pp->getN_ack_value();
        case FIELD_mycheckbits: return pp->getMycheckbits();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'CustomizedMsg_Base' as cValue -- field index out of range?", field);
    }
}

void CustomizedMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CustomizedMsg_Base *pp = omnetpp::fromAnyPtr<CustomizedMsg_Base>(object); (void)pp;
    switch (field) {
        case FIELD_seq_num: pp->setSeq_num(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_frame_type: pp->setFrame_type(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_msg_payload: pp->setMsg_payload(value.stringValue()); break;
        case FIELD_n_ack_value: pp->setN_ack_value(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_mycheckbits: pp->setMycheckbits(omnetpp::checked_int_cast<char>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CustomizedMsg_Base'", field);
    }
}

const char *CustomizedMsgDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr CustomizedMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    CustomizedMsg_Base *pp = omnetpp::fromAnyPtr<CustomizedMsg_Base>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void CustomizedMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    CustomizedMsg_Base *pp = omnetpp::fromAnyPtr<CustomizedMsg_Base>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CustomizedMsg_Base'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

