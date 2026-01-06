//
// Generated file, do not edit! Created by opp_msgtool 6.0 from group.msg.
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
#include "group_m.h"

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

Register_Class(values)

values::values(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

values::values(const values& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

values::~values()
{
}

values& values::operator=(const values& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void values::copy(const values& other)
{
    this->label = other.label;
    this->id = other.id;
    this->time = other.time;
    this->batterie = other.batterie;
    this->byteLength = other.byteLength;
}

void values::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->label);
    doParsimPacking(b,this->id);
    doParsimPacking(b,this->time);
    doParsimPacking(b,this->batterie);
    doParsimPacking(b,this->byteLength);
}

void values::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->label);
    doParsimUnpacking(b,this->id);
    doParsimUnpacking(b,this->time);
    doParsimUnpacking(b,this->batterie);
    doParsimUnpacking(b,this->byteLength);
}

int values::getLabel() const
{
    return this->label;
}

void values::setLabel(int label)
{
    this->label = label;
}

const char * values::getId() const
{
    return this->id.c_str();
}

void values::setId(const char * id)
{
    this->id = id;
}

omnetpp::simtime_t values::getTime() const
{
    return this->time;
}

void values::setTime(omnetpp::simtime_t time)
{
    this->time = time;
}

int values::getBatterie() const
{
    return this->batterie;
}

void values::setBatterie(int batterie)
{
    this->batterie = batterie;
}

int values::getByteLength() const
{
    return this->byteLength;
}

void values::setByteLength(int byteLength)
{
    this->byteLength = byteLength;
}

class valuesDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_label,
        FIELD_id,
        FIELD_time,
        FIELD_batterie,
        FIELD_byteLength,
    };
  public:
    valuesDescriptor();
    virtual ~valuesDescriptor();

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

Register_ClassDescriptor(valuesDescriptor)

valuesDescriptor::valuesDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(values)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

valuesDescriptor::~valuesDescriptor()
{
    delete[] propertyNames;
}

bool valuesDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<values *>(obj)!=nullptr;
}

const char **valuesDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *valuesDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int valuesDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int valuesDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_label
        FD_ISEDITABLE,    // FIELD_id
        FD_ISEDITABLE,    // FIELD_time
        FD_ISEDITABLE,    // FIELD_batterie
        FD_ISEDITABLE,    // FIELD_byteLength
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *valuesDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "label",
        "id",
        "time",
        "batterie",
        "byteLength",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int valuesDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "label") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "id") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "time") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "batterie") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "byteLength") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *valuesDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_label
        "string",    // FIELD_id
        "omnetpp::simtime_t",    // FIELD_time
        "int",    // FIELD_batterie
        "int",    // FIELD_byteLength
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **valuesDescriptor::getFieldPropertyNames(int field) const
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

const char *valuesDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int valuesDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    values *pp = omnetpp::fromAnyPtr<values>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void valuesDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    values *pp = omnetpp::fromAnyPtr<values>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'values'", field);
    }
}

const char *valuesDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    values *pp = omnetpp::fromAnyPtr<values>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string valuesDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    values *pp = omnetpp::fromAnyPtr<values>(object); (void)pp;
    switch (field) {
        case FIELD_label: return long2string(pp->getLabel());
        case FIELD_id: return oppstring2string(pp->getId());
        case FIELD_time: return simtime2string(pp->getTime());
        case FIELD_batterie: return long2string(pp->getBatterie());
        case FIELD_byteLength: return long2string(pp->getByteLength());
        default: return "";
    }
}

void valuesDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    values *pp = omnetpp::fromAnyPtr<values>(object); (void)pp;
    switch (field) {
        case FIELD_label: pp->setLabel(string2long(value)); break;
        case FIELD_id: pp->setId((value)); break;
        case FIELD_time: pp->setTime(string2simtime(value)); break;
        case FIELD_batterie: pp->setBatterie(string2long(value)); break;
        case FIELD_byteLength: pp->setByteLength(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'values'", field);
    }
}

omnetpp::cValue valuesDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    values *pp = omnetpp::fromAnyPtr<values>(object); (void)pp;
    switch (field) {
        case FIELD_label: return pp->getLabel();
        case FIELD_id: return pp->getId();
        case FIELD_time: return pp->getTime().dbl();
        case FIELD_batterie: return pp->getBatterie();
        case FIELD_byteLength: return pp->getByteLength();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'values' as cValue -- field index out of range?", field);
    }
}

void valuesDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    values *pp = omnetpp::fromAnyPtr<values>(object); (void)pp;
    switch (field) {
        case FIELD_label: pp->setLabel(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_id: pp->setId(value.stringValue()); break;
        case FIELD_time: pp->setTime(value.doubleValue()); break;
        case FIELD_batterie: pp->setBatterie(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_byteLength: pp->setByteLength(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'values'", field);
    }
}

const char *valuesDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr valuesDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    values *pp = omnetpp::fromAnyPtr<values>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void valuesDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    values *pp = omnetpp::fromAnyPtr<values>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'values'", field);
    }
}

Register_Class(sensors_trust)

sensors_trust::sensors_trust(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

sensors_trust::sensors_trust(const sensors_trust& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

sensors_trust::~sensors_trust()
{
}

sensors_trust& sensors_trust::operator=(const sensors_trust& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void sensors_trust::copy(const sensors_trust& other)
{
    this->node = other.node;
    this->tr = other.tr;
}

void sensors_trust::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->node);
    doParsimPacking(b,this->tr);
}

void sensors_trust::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->node);
    doParsimUnpacking(b,this->tr);
}

const char * sensors_trust::getNode() const
{
    return this->node.c_str();
}

void sensors_trust::setNode(const char * node)
{
    this->node = node;
}

double sensors_trust::getTr() const
{
    return this->tr;
}

void sensors_trust::setTr(double tr)
{
    this->tr = tr;
}

class sensors_trustDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_node,
        FIELD_tr,
    };
  public:
    sensors_trustDescriptor();
    virtual ~sensors_trustDescriptor();

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

Register_ClassDescriptor(sensors_trustDescriptor)

sensors_trustDescriptor::sensors_trustDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(sensors_trust)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

sensors_trustDescriptor::~sensors_trustDescriptor()
{
    delete[] propertyNames;
}

bool sensors_trustDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<sensors_trust *>(obj)!=nullptr;
}

const char **sensors_trustDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *sensors_trustDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int sensors_trustDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int sensors_trustDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_node
        FD_ISEDITABLE,    // FIELD_tr
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *sensors_trustDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "node",
        "tr",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int sensors_trustDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "node") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "tr") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *sensors_trustDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_node
        "double",    // FIELD_tr
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **sensors_trustDescriptor::getFieldPropertyNames(int field) const
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

const char *sensors_trustDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int sensors_trustDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    sensors_trust *pp = omnetpp::fromAnyPtr<sensors_trust>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void sensors_trustDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    sensors_trust *pp = omnetpp::fromAnyPtr<sensors_trust>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'sensors_trust'", field);
    }
}

const char *sensors_trustDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    sensors_trust *pp = omnetpp::fromAnyPtr<sensors_trust>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string sensors_trustDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    sensors_trust *pp = omnetpp::fromAnyPtr<sensors_trust>(object); (void)pp;
    switch (field) {
        case FIELD_node: return oppstring2string(pp->getNode());
        case FIELD_tr: return double2string(pp->getTr());
        default: return "";
    }
}

void sensors_trustDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    sensors_trust *pp = omnetpp::fromAnyPtr<sensors_trust>(object); (void)pp;
    switch (field) {
        case FIELD_node: pp->setNode((value)); break;
        case FIELD_tr: pp->setTr(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'sensors_trust'", field);
    }
}

omnetpp::cValue sensors_trustDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    sensors_trust *pp = omnetpp::fromAnyPtr<sensors_trust>(object); (void)pp;
    switch (field) {
        case FIELD_node: return pp->getNode();
        case FIELD_tr: return pp->getTr();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'sensors_trust' as cValue -- field index out of range?", field);
    }
}

void sensors_trustDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    sensors_trust *pp = omnetpp::fromAnyPtr<sensors_trust>(object); (void)pp;
    switch (field) {
        case FIELD_node: pp->setNode(value.stringValue()); break;
        case FIELD_tr: pp->setTr(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'sensors_trust'", field);
    }
}

const char *sensors_trustDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr sensors_trustDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    sensors_trust *pp = omnetpp::fromAnyPtr<sensors_trust>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void sensors_trustDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    sensors_trust *pp = omnetpp::fromAnyPtr<sensors_trust>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'sensors_trust'", field);
    }
}

Register_Class(request)

request::request(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

request::request(const request& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

request::~request()
{
}

request& request::operator=(const request& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void request::copy(const request& other)
{
    this->node = other.node;
    this->need = other.need;
}

void request::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->node);
    doParsimPacking(b,this->need);
}

void request::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->node);
    doParsimUnpacking(b,this->need);
}

const char * request::getNode() const
{
    return this->node.c_str();
}

void request::setNode(const char * node)
{
    this->node = node;
}

double request::getNeed() const
{
    return this->need;
}

void request::setNeed(double need)
{
    this->need = need;
}

class requestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_node,
        FIELD_need,
    };
  public:
    requestDescriptor();
    virtual ~requestDescriptor();

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

Register_ClassDescriptor(requestDescriptor)

requestDescriptor::requestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(request)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

requestDescriptor::~requestDescriptor()
{
    delete[] propertyNames;
}

bool requestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<request *>(obj)!=nullptr;
}

const char **requestDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *requestDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int requestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int requestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_node
        FD_ISEDITABLE,    // FIELD_need
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *requestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "node",
        "need",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int requestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "node") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "need") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *requestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_node
        "double",    // FIELD_need
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **requestDescriptor::getFieldPropertyNames(int field) const
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

const char *requestDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int requestDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    request *pp = omnetpp::fromAnyPtr<request>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void requestDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    request *pp = omnetpp::fromAnyPtr<request>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'request'", field);
    }
}

const char *requestDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    request *pp = omnetpp::fromAnyPtr<request>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string requestDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    request *pp = omnetpp::fromAnyPtr<request>(object); (void)pp;
    switch (field) {
        case FIELD_node: return oppstring2string(pp->getNode());
        case FIELD_need: return double2string(pp->getNeed());
        default: return "";
    }
}

void requestDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    request *pp = omnetpp::fromAnyPtr<request>(object); (void)pp;
    switch (field) {
        case FIELD_node: pp->setNode((value)); break;
        case FIELD_need: pp->setNeed(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'request'", field);
    }
}

omnetpp::cValue requestDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    request *pp = omnetpp::fromAnyPtr<request>(object); (void)pp;
    switch (field) {
        case FIELD_node: return pp->getNode();
        case FIELD_need: return pp->getNeed();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'request' as cValue -- field index out of range?", field);
    }
}

void requestDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    request *pp = omnetpp::fromAnyPtr<request>(object); (void)pp;
    switch (field) {
        case FIELD_node: pp->setNode(value.stringValue()); break;
        case FIELD_need: pp->setNeed(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'request'", field);
    }
}

const char *requestDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr requestDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    request *pp = omnetpp::fromAnyPtr<request>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void requestDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    request *pp = omnetpp::fromAnyPtr<request>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'request'", field);
    }
}

Register_Class(offer)

offer::offer(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

offer::offer(const offer& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

offer::~offer()
{
}

offer& offer::operator=(const offer& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void offer::copy(const offer& other)
{
    this->node = other.node;
    this->offre = other.offre;
}

void offer::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->node);
    doParsimPacking(b,this->offre);
}

void offer::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->node);
    doParsimUnpacking(b,this->offre);
}

const char * offer::getNode() const
{
    return this->node.c_str();
}

void offer::setNode(const char * node)
{
    this->node = node;
}

double offer::getOffre() const
{
    return this->offre;
}

void offer::setOffre(double offre)
{
    this->offre = offre;
}

class offerDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_node,
        FIELD_offre,
    };
  public:
    offerDescriptor();
    virtual ~offerDescriptor();

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

Register_ClassDescriptor(offerDescriptor)

offerDescriptor::offerDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(offer)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

offerDescriptor::~offerDescriptor()
{
    delete[] propertyNames;
}

bool offerDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<offer *>(obj)!=nullptr;
}

const char **offerDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *offerDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int offerDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int offerDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_node
        FD_ISEDITABLE,    // FIELD_offre
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *offerDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "node",
        "offre",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int offerDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "node") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "offre") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *offerDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_node
        "double",    // FIELD_offre
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **offerDescriptor::getFieldPropertyNames(int field) const
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

const char *offerDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int offerDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    offer *pp = omnetpp::fromAnyPtr<offer>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void offerDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    offer *pp = omnetpp::fromAnyPtr<offer>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'offer'", field);
    }
}

const char *offerDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    offer *pp = omnetpp::fromAnyPtr<offer>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string offerDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    offer *pp = omnetpp::fromAnyPtr<offer>(object); (void)pp;
    switch (field) {
        case FIELD_node: return oppstring2string(pp->getNode());
        case FIELD_offre: return double2string(pp->getOffre());
        default: return "";
    }
}

void offerDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    offer *pp = omnetpp::fromAnyPtr<offer>(object); (void)pp;
    switch (field) {
        case FIELD_node: pp->setNode((value)); break;
        case FIELD_offre: pp->setOffre(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'offer'", field);
    }
}

omnetpp::cValue offerDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    offer *pp = omnetpp::fromAnyPtr<offer>(object); (void)pp;
    switch (field) {
        case FIELD_node: return pp->getNode();
        case FIELD_offre: return pp->getOffre();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'offer' as cValue -- field index out of range?", field);
    }
}

void offerDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    offer *pp = omnetpp::fromAnyPtr<offer>(object); (void)pp;
    switch (field) {
        case FIELD_node: pp->setNode(value.stringValue()); break;
        case FIELD_offre: pp->setOffre(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'offer'", field);
    }
}

const char *offerDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr offerDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    offer *pp = omnetpp::fromAnyPtr<offer>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void offerDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    offer *pp = omnetpp::fromAnyPtr<offer>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'offer'", field);
    }
}

Register_Class(sp_to_sc)

sp_to_sc::sp_to_sc(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

sp_to_sc::sp_to_sc(const sp_to_sc& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

sp_to_sc::~sp_to_sc()
{
}

sp_to_sc& sp_to_sc::operator=(const sp_to_sc& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void sp_to_sc::copy(const sp_to_sc& other)
{
    this->sc = other.sc;
    this->sp = other.sp;
    this->need = other.need;
    this->service = other.service;
}

void sp_to_sc::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->sc);
    doParsimPacking(b,this->sp);
    doParsimPacking(b,this->need);
    doParsimPacking(b,this->service);
}

void sp_to_sc::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->sc);
    doParsimUnpacking(b,this->sp);
    doParsimUnpacking(b,this->need);
    doParsimUnpacking(b,this->service);
}

const char * sp_to_sc::getSc() const
{
    return this->sc.c_str();
}

void sp_to_sc::setSc(const char * sc)
{
    this->sc = sc;
}

const char * sp_to_sc::getSp() const
{
    return this->sp.c_str();
}

void sp_to_sc::setSp(const char * sp)
{
    this->sp = sp;
}

double sp_to_sc::getNeed() const
{
    return this->need;
}

void sp_to_sc::setNeed(double need)
{
    this->need = need;
}

double sp_to_sc::getService() const
{
    return this->service;
}

void sp_to_sc::setService(double service)
{
    this->service = service;
}

class sp_to_scDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sc,
        FIELD_sp,
        FIELD_need,
        FIELD_service,
    };
  public:
    sp_to_scDescriptor();
    virtual ~sp_to_scDescriptor();

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

Register_ClassDescriptor(sp_to_scDescriptor)

sp_to_scDescriptor::sp_to_scDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(sp_to_sc)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

sp_to_scDescriptor::~sp_to_scDescriptor()
{
    delete[] propertyNames;
}

bool sp_to_scDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<sp_to_sc *>(obj)!=nullptr;
}

const char **sp_to_scDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *sp_to_scDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int sp_to_scDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int sp_to_scDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sc
        FD_ISEDITABLE,    // FIELD_sp
        FD_ISEDITABLE,    // FIELD_need
        FD_ISEDITABLE,    // FIELD_service
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *sp_to_scDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sc",
        "sp",
        "need",
        "service",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int sp_to_scDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sc") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "sp") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "need") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "service") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *sp_to_scDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_sc
        "string",    // FIELD_sp
        "double",    // FIELD_need
        "double",    // FIELD_service
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **sp_to_scDescriptor::getFieldPropertyNames(int field) const
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

const char *sp_to_scDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int sp_to_scDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    sp_to_sc *pp = omnetpp::fromAnyPtr<sp_to_sc>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void sp_to_scDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    sp_to_sc *pp = omnetpp::fromAnyPtr<sp_to_sc>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'sp_to_sc'", field);
    }
}

const char *sp_to_scDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    sp_to_sc *pp = omnetpp::fromAnyPtr<sp_to_sc>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string sp_to_scDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    sp_to_sc *pp = omnetpp::fromAnyPtr<sp_to_sc>(object); (void)pp;
    switch (field) {
        case FIELD_sc: return oppstring2string(pp->getSc());
        case FIELD_sp: return oppstring2string(pp->getSp());
        case FIELD_need: return double2string(pp->getNeed());
        case FIELD_service: return double2string(pp->getService());
        default: return "";
    }
}

void sp_to_scDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    sp_to_sc *pp = omnetpp::fromAnyPtr<sp_to_sc>(object); (void)pp;
    switch (field) {
        case FIELD_sc: pp->setSc((value)); break;
        case FIELD_sp: pp->setSp((value)); break;
        case FIELD_need: pp->setNeed(string2double(value)); break;
        case FIELD_service: pp->setService(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'sp_to_sc'", field);
    }
}

omnetpp::cValue sp_to_scDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    sp_to_sc *pp = omnetpp::fromAnyPtr<sp_to_sc>(object); (void)pp;
    switch (field) {
        case FIELD_sc: return pp->getSc();
        case FIELD_sp: return pp->getSp();
        case FIELD_need: return pp->getNeed();
        case FIELD_service: return pp->getService();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'sp_to_sc' as cValue -- field index out of range?", field);
    }
}

void sp_to_scDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    sp_to_sc *pp = omnetpp::fromAnyPtr<sp_to_sc>(object); (void)pp;
    switch (field) {
        case FIELD_sc: pp->setSc(value.stringValue()); break;
        case FIELD_sp: pp->setSp(value.stringValue()); break;
        case FIELD_need: pp->setNeed(value.doubleValue()); break;
        case FIELD_service: pp->setService(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'sp_to_sc'", field);
    }
}

const char *sp_to_scDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr sp_to_scDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    sp_to_sc *pp = omnetpp::fromAnyPtr<sp_to_sc>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void sp_to_scDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    sp_to_sc *pp = omnetpp::fromAnyPtr<sp_to_sc>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'sp_to_sc'", field);
    }
}

Register_Class(req_to_sp)

req_to_sp::req_to_sp(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

req_to_sp::req_to_sp(const req_to_sp& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

req_to_sp::~req_to_sp()
{
}

req_to_sp& req_to_sp::operator=(const req_to_sp& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void req_to_sp::copy(const req_to_sp& other)
{
    this->sp = other.sp;
    this->sc = other.sc;
    this->need = other.need;
    this->service = other.service;
}

void req_to_sp::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->sp);
    doParsimPacking(b,this->sc);
    doParsimPacking(b,this->need);
    doParsimPacking(b,this->service);
}

void req_to_sp::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->sp);
    doParsimUnpacking(b,this->sc);
    doParsimUnpacking(b,this->need);
    doParsimUnpacking(b,this->service);
}

const char * req_to_sp::getSp() const
{
    return this->sp.c_str();
}

void req_to_sp::setSp(const char * sp)
{
    this->sp = sp;
}

const char * req_to_sp::getSc() const
{
    return this->sc.c_str();
}

void req_to_sp::setSc(const char * sc)
{
    this->sc = sc;
}

double req_to_sp::getNeed() const
{
    return this->need;
}

void req_to_sp::setNeed(double need)
{
    this->need = need;
}

double req_to_sp::getService() const
{
    return this->service;
}

void req_to_sp::setService(double service)
{
    this->service = service;
}

class req_to_spDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sp,
        FIELD_sc,
        FIELD_need,
        FIELD_service,
    };
  public:
    req_to_spDescriptor();
    virtual ~req_to_spDescriptor();

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

Register_ClassDescriptor(req_to_spDescriptor)

req_to_spDescriptor::req_to_spDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(req_to_sp)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

req_to_spDescriptor::~req_to_spDescriptor()
{
    delete[] propertyNames;
}

bool req_to_spDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<req_to_sp *>(obj)!=nullptr;
}

const char **req_to_spDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *req_to_spDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int req_to_spDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int req_to_spDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sp
        FD_ISEDITABLE,    // FIELD_sc
        FD_ISEDITABLE,    // FIELD_need
        FD_ISEDITABLE,    // FIELD_service
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *req_to_spDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sp",
        "sc",
        "need",
        "service",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int req_to_spDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sp") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "sc") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "need") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "service") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *req_to_spDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_sp
        "string",    // FIELD_sc
        "double",    // FIELD_need
        "double",    // FIELD_service
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **req_to_spDescriptor::getFieldPropertyNames(int field) const
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

const char *req_to_spDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int req_to_spDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    req_to_sp *pp = omnetpp::fromAnyPtr<req_to_sp>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void req_to_spDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    req_to_sp *pp = omnetpp::fromAnyPtr<req_to_sp>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'req_to_sp'", field);
    }
}

const char *req_to_spDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    req_to_sp *pp = omnetpp::fromAnyPtr<req_to_sp>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string req_to_spDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    req_to_sp *pp = omnetpp::fromAnyPtr<req_to_sp>(object); (void)pp;
    switch (field) {
        case FIELD_sp: return oppstring2string(pp->getSp());
        case FIELD_sc: return oppstring2string(pp->getSc());
        case FIELD_need: return double2string(pp->getNeed());
        case FIELD_service: return double2string(pp->getService());
        default: return "";
    }
}

void req_to_spDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    req_to_sp *pp = omnetpp::fromAnyPtr<req_to_sp>(object); (void)pp;
    switch (field) {
        case FIELD_sp: pp->setSp((value)); break;
        case FIELD_sc: pp->setSc((value)); break;
        case FIELD_need: pp->setNeed(string2double(value)); break;
        case FIELD_service: pp->setService(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'req_to_sp'", field);
    }
}

omnetpp::cValue req_to_spDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    req_to_sp *pp = omnetpp::fromAnyPtr<req_to_sp>(object); (void)pp;
    switch (field) {
        case FIELD_sp: return pp->getSp();
        case FIELD_sc: return pp->getSc();
        case FIELD_need: return pp->getNeed();
        case FIELD_service: return pp->getService();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'req_to_sp' as cValue -- field index out of range?", field);
    }
}

void req_to_spDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    req_to_sp *pp = omnetpp::fromAnyPtr<req_to_sp>(object); (void)pp;
    switch (field) {
        case FIELD_sp: pp->setSp(value.stringValue()); break;
        case FIELD_sc: pp->setSc(value.stringValue()); break;
        case FIELD_need: pp->setNeed(value.doubleValue()); break;
        case FIELD_service: pp->setService(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'req_to_sp'", field);
    }
}

const char *req_to_spDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr req_to_spDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    req_to_sp *pp = omnetpp::fromAnyPtr<req_to_sp>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void req_to_spDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    req_to_sp *pp = omnetpp::fromAnyPtr<req_to_sp>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'req_to_sp'", field);
    }
}

Register_Class(ser_to_sc)

ser_to_sc::ser_to_sc(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

ser_to_sc::ser_to_sc(const ser_to_sc& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

ser_to_sc::~ser_to_sc()
{
}

ser_to_sc& ser_to_sc::operator=(const ser_to_sc& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void ser_to_sc::copy(const ser_to_sc& other)
{
    this->sc = other.sc;
    this->sp = other.sp;
    this->need = other.need;
    this->service = other.service;
}

void ser_to_sc::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->sc);
    doParsimPacking(b,this->sp);
    doParsimPacking(b,this->need);
    doParsimPacking(b,this->service);
}

void ser_to_sc::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->sc);
    doParsimUnpacking(b,this->sp);
    doParsimUnpacking(b,this->need);
    doParsimUnpacking(b,this->service);
}

const char * ser_to_sc::getSc() const
{
    return this->sc.c_str();
}

void ser_to_sc::setSc(const char * sc)
{
    this->sc = sc;
}

const char * ser_to_sc::getSp() const
{
    return this->sp.c_str();
}

void ser_to_sc::setSp(const char * sp)
{
    this->sp = sp;
}

double ser_to_sc::getNeed() const
{
    return this->need;
}

void ser_to_sc::setNeed(double need)
{
    this->need = need;
}

double ser_to_sc::getService() const
{
    return this->service;
}

void ser_to_sc::setService(double service)
{
    this->service = service;
}

class ser_to_scDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sc,
        FIELD_sp,
        FIELD_need,
        FIELD_service,
    };
  public:
    ser_to_scDescriptor();
    virtual ~ser_to_scDescriptor();

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

Register_ClassDescriptor(ser_to_scDescriptor)

ser_to_scDescriptor::ser_to_scDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(ser_to_sc)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

ser_to_scDescriptor::~ser_to_scDescriptor()
{
    delete[] propertyNames;
}

bool ser_to_scDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ser_to_sc *>(obj)!=nullptr;
}

const char **ser_to_scDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ser_to_scDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ser_to_scDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int ser_to_scDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sc
        FD_ISEDITABLE,    // FIELD_sp
        FD_ISEDITABLE,    // FIELD_need
        FD_ISEDITABLE,    // FIELD_service
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *ser_to_scDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sc",
        "sp",
        "need",
        "service",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int ser_to_scDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sc") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "sp") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "need") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "service") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *ser_to_scDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_sc
        "string",    // FIELD_sp
        "double",    // FIELD_need
        "double",    // FIELD_service
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **ser_to_scDescriptor::getFieldPropertyNames(int field) const
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

const char *ser_to_scDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int ser_to_scDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ser_to_sc *pp = omnetpp::fromAnyPtr<ser_to_sc>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ser_to_scDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ser_to_sc *pp = omnetpp::fromAnyPtr<ser_to_sc>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ser_to_sc'", field);
    }
}

const char *ser_to_scDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ser_to_sc *pp = omnetpp::fromAnyPtr<ser_to_sc>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ser_to_scDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ser_to_sc *pp = omnetpp::fromAnyPtr<ser_to_sc>(object); (void)pp;
    switch (field) {
        case FIELD_sc: return oppstring2string(pp->getSc());
        case FIELD_sp: return oppstring2string(pp->getSp());
        case FIELD_need: return double2string(pp->getNeed());
        case FIELD_service: return double2string(pp->getService());
        default: return "";
    }
}

void ser_to_scDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ser_to_sc *pp = omnetpp::fromAnyPtr<ser_to_sc>(object); (void)pp;
    switch (field) {
        case FIELD_sc: pp->setSc((value)); break;
        case FIELD_sp: pp->setSp((value)); break;
        case FIELD_need: pp->setNeed(string2double(value)); break;
        case FIELD_service: pp->setService(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ser_to_sc'", field);
    }
}

omnetpp::cValue ser_to_scDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ser_to_sc *pp = omnetpp::fromAnyPtr<ser_to_sc>(object); (void)pp;
    switch (field) {
        case FIELD_sc: return pp->getSc();
        case FIELD_sp: return pp->getSp();
        case FIELD_need: return pp->getNeed();
        case FIELD_service: return pp->getService();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ser_to_sc' as cValue -- field index out of range?", field);
    }
}

void ser_to_scDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ser_to_sc *pp = omnetpp::fromAnyPtr<ser_to_sc>(object); (void)pp;
    switch (field) {
        case FIELD_sc: pp->setSc(value.stringValue()); break;
        case FIELD_sp: pp->setSp(value.stringValue()); break;
        case FIELD_need: pp->setNeed(value.doubleValue()); break;
        case FIELD_service: pp->setService(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ser_to_sc'", field);
    }
}

const char *ser_to_scDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr ser_to_scDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ser_to_sc *pp = omnetpp::fromAnyPtr<ser_to_sc>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ser_to_scDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ser_to_sc *pp = omnetpp::fromAnyPtr<ser_to_sc>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ser_to_sc'", field);
    }
}

Register_Class(fb_to_cloud)

fb_to_cloud::fb_to_cloud(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

fb_to_cloud::fb_to_cloud(const fb_to_cloud& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

fb_to_cloud::~fb_to_cloud()
{
}

fb_to_cloud& fb_to_cloud::operator=(const fb_to_cloud& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void fb_to_cloud::copy(const fb_to_cloud& other)
{
    this->sp = other.sp;
    this->sc = other.sc;
    this->fb = other.fb;
}

void fb_to_cloud::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->sp);
    doParsimPacking(b,this->sc);
    doParsimPacking(b,this->fb);
}

void fb_to_cloud::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->sp);
    doParsimUnpacking(b,this->sc);
    doParsimUnpacking(b,this->fb);
}

const char * fb_to_cloud::getSp() const
{
    return this->sp.c_str();
}

void fb_to_cloud::setSp(const char * sp)
{
    this->sp = sp;
}

const char * fb_to_cloud::getSc() const
{
    return this->sc.c_str();
}

void fb_to_cloud::setSc(const char * sc)
{
    this->sc = sc;
}

double fb_to_cloud::getFb() const
{
    return this->fb;
}

void fb_to_cloud::setFb(double fb)
{
    this->fb = fb;
}

class fb_to_cloudDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sp,
        FIELD_sc,
        FIELD_fb,
    };
  public:
    fb_to_cloudDescriptor();
    virtual ~fb_to_cloudDescriptor();

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

Register_ClassDescriptor(fb_to_cloudDescriptor)

fb_to_cloudDescriptor::fb_to_cloudDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(fb_to_cloud)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

fb_to_cloudDescriptor::~fb_to_cloudDescriptor()
{
    delete[] propertyNames;
}

bool fb_to_cloudDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<fb_to_cloud *>(obj)!=nullptr;
}

const char **fb_to_cloudDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *fb_to_cloudDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int fb_to_cloudDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int fb_to_cloudDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sp
        FD_ISEDITABLE,    // FIELD_sc
        FD_ISEDITABLE,    // FIELD_fb
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *fb_to_cloudDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sp",
        "sc",
        "fb",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int fb_to_cloudDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sp") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "sc") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "fb") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *fb_to_cloudDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_sp
        "string",    // FIELD_sc
        "double",    // FIELD_fb
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **fb_to_cloudDescriptor::getFieldPropertyNames(int field) const
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

const char *fb_to_cloudDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int fb_to_cloudDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    fb_to_cloud *pp = omnetpp::fromAnyPtr<fb_to_cloud>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void fb_to_cloudDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    fb_to_cloud *pp = omnetpp::fromAnyPtr<fb_to_cloud>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'fb_to_cloud'", field);
    }
}

const char *fb_to_cloudDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    fb_to_cloud *pp = omnetpp::fromAnyPtr<fb_to_cloud>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string fb_to_cloudDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    fb_to_cloud *pp = omnetpp::fromAnyPtr<fb_to_cloud>(object); (void)pp;
    switch (field) {
        case FIELD_sp: return oppstring2string(pp->getSp());
        case FIELD_sc: return oppstring2string(pp->getSc());
        case FIELD_fb: return double2string(pp->getFb());
        default: return "";
    }
}

void fb_to_cloudDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    fb_to_cloud *pp = omnetpp::fromAnyPtr<fb_to_cloud>(object); (void)pp;
    switch (field) {
        case FIELD_sp: pp->setSp((value)); break;
        case FIELD_sc: pp->setSc((value)); break;
        case FIELD_fb: pp->setFb(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'fb_to_cloud'", field);
    }
}

omnetpp::cValue fb_to_cloudDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    fb_to_cloud *pp = omnetpp::fromAnyPtr<fb_to_cloud>(object); (void)pp;
    switch (field) {
        case FIELD_sp: return pp->getSp();
        case FIELD_sc: return pp->getSc();
        case FIELD_fb: return pp->getFb();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'fb_to_cloud' as cValue -- field index out of range?", field);
    }
}

void fb_to_cloudDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    fb_to_cloud *pp = omnetpp::fromAnyPtr<fb_to_cloud>(object); (void)pp;
    switch (field) {
        case FIELD_sp: pp->setSp(value.stringValue()); break;
        case FIELD_sc: pp->setSc(value.stringValue()); break;
        case FIELD_fb: pp->setFb(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'fb_to_cloud'", field);
    }
}

const char *fb_to_cloudDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr fb_to_cloudDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    fb_to_cloud *pp = omnetpp::fromAnyPtr<fb_to_cloud>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void fb_to_cloudDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    fb_to_cloud *pp = omnetpp::fromAnyPtr<fb_to_cloud>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'fb_to_cloud'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

