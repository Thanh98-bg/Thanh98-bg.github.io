//
// Generated file, do not edit! Created by nedtool 5.6 from MessageType.msg.
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
#include "MessageType_m.h"

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
    for (int i=0; i<n; i++) {
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
    for (int i=0; i<n; i++) {
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
    for (int i=0; i<n; i++) {
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


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(ClusterMessage)

ClusterMessage::ClusterMessage(const char *name, short kind) : ::omnetpp::cMessage(name,kind)
{
    this->proto = 0;
    this->srcAddress = 0;
    this->destAddress = 0;
}

ClusterMessage::ClusterMessage(const ClusterMessage& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

ClusterMessage::~ClusterMessage()
{
}

ClusterMessage& ClusterMessage::operator=(const ClusterMessage& other)
{
    if (this==&other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void ClusterMessage::copy(const ClusterMessage& other)
{
    this->proto = other.proto;
    this->srcAddress = other.srcAddress;
    this->destAddress = other.destAddress;
}

void ClusterMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->proto);
    doParsimPacking(b,this->srcAddress);
    doParsimPacking(b,this->destAddress);
}

void ClusterMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->proto);
    doParsimUnpacking(b,this->srcAddress);
    doParsimUnpacking(b,this->destAddress);
}

int ClusterMessage::getProto() const
{
    return this->proto;
}

void ClusterMessage::setProto(int proto)
{
    this->proto = proto;
}

int ClusterMessage::getSrcAddress() const
{
    return this->srcAddress;
}

void ClusterMessage::setSrcAddress(int srcAddress)
{
    this->srcAddress = srcAddress;
}

int ClusterMessage::getDestAddress() const
{
    return this->destAddress;
}

void ClusterMessage::setDestAddress(int destAddress)
{
    this->destAddress = destAddress;
}

class ClusterMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    ClusterMessageDescriptor();
    virtual ~ClusterMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(ClusterMessageDescriptor)

ClusterMessageDescriptor::ClusterMessageDescriptor() : omnetpp::cClassDescriptor("ClusterMessage", "omnetpp::cMessage")
{
    propertynames = nullptr;
}

ClusterMessageDescriptor::~ClusterMessageDescriptor()
{
    delete[] propertynames;
}

bool ClusterMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ClusterMessage *>(obj)!=nullptr;
}

const char **ClusterMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *ClusterMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int ClusterMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int ClusterMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *ClusterMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "proto",
        "srcAddress",
        "destAddress",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int ClusterMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "proto")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcAddress")==0) return base+1;
    if (fieldName[0]=='d' && strcmp(fieldName, "destAddress")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *ClusterMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **ClusterMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *ClusterMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int ClusterMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    ClusterMessage *pp = (ClusterMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *ClusterMessageDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ClusterMessage *pp = (ClusterMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ClusterMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ClusterMessage *pp = (ClusterMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getProto());
        case 1: return long2string(pp->getSrcAddress());
        case 2: return long2string(pp->getDestAddress());
        default: return "";
    }
}

bool ClusterMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    ClusterMessage *pp = (ClusterMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setProto(string2long(value)); return true;
        case 1: pp->setSrcAddress(string2long(value)); return true;
        case 2: pp->setDestAddress(string2long(value)); return true;
        default: return false;
    }
}

const char *ClusterMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *ClusterMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    ClusterMessage *pp = (ClusterMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(ReqClusterMessage)

ReqClusterMessage::ReqClusterMessage(const char *name, short kind) : ::ClusterMessage(name,kind)
{
    this->energy = 0;
    this->FCH = 0;
    this->nrMemEvent = 0;
}

ReqClusterMessage::ReqClusterMessage(const ReqClusterMessage& other) : ::ClusterMessage(other)
{
    copy(other);
}

ReqClusterMessage::~ReqClusterMessage()
{
}

ReqClusterMessage& ReqClusterMessage::operator=(const ReqClusterMessage& other)
{
    if (this==&other) return *this;
    ::ClusterMessage::operator=(other);
    copy(other);
    return *this;
}

void ReqClusterMessage::copy(const ReqClusterMessage& other)
{
    this->energy = other.energy;
    this->FCH = other.FCH;
    this->nrMemEvent = other.nrMemEvent;
}

void ReqClusterMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::ClusterMessage::parsimPack(b);
    doParsimPacking(b,this->energy);
    doParsimPacking(b,this->FCH);
    doParsimPacking(b,this->nrMemEvent);
}

void ReqClusterMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::ClusterMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->energy);
    doParsimUnpacking(b,this->FCH);
    doParsimUnpacking(b,this->nrMemEvent);
}

int ReqClusterMessage::getEnergy() const
{
    return this->energy;
}

void ReqClusterMessage::setEnergy(int energy)
{
    this->energy = energy;
}

double ReqClusterMessage::getFCH() const
{
    return this->FCH;
}

void ReqClusterMessage::setFCH(double FCH)
{
    this->FCH = FCH;
}

int ReqClusterMessage::getNrMemEvent() const
{
    return this->nrMemEvent;
}

void ReqClusterMessage::setNrMemEvent(int nrMemEvent)
{
    this->nrMemEvent = nrMemEvent;
}

class ReqClusterMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    ReqClusterMessageDescriptor();
    virtual ~ReqClusterMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(ReqClusterMessageDescriptor)

ReqClusterMessageDescriptor::ReqClusterMessageDescriptor() : omnetpp::cClassDescriptor("ReqClusterMessage", "ClusterMessage")
{
    propertynames = nullptr;
}

ReqClusterMessageDescriptor::~ReqClusterMessageDescriptor()
{
    delete[] propertynames;
}

bool ReqClusterMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ReqClusterMessage *>(obj)!=nullptr;
}

const char **ReqClusterMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *ReqClusterMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int ReqClusterMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int ReqClusterMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *ReqClusterMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "energy",
        "FCH",
        "nrMemEvent",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int ReqClusterMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='e' && strcmp(fieldName, "energy")==0) return base+0;
    if (fieldName[0]=='F' && strcmp(fieldName, "FCH")==0) return base+1;
    if (fieldName[0]=='n' && strcmp(fieldName, "nrMemEvent")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *ReqClusterMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "double",
        "int",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **ReqClusterMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *ReqClusterMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int ReqClusterMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    ReqClusterMessage *pp = (ReqClusterMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *ReqClusterMessageDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ReqClusterMessage *pp = (ReqClusterMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ReqClusterMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ReqClusterMessage *pp = (ReqClusterMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getEnergy());
        case 1: return double2string(pp->getFCH());
        case 2: return long2string(pp->getNrMemEvent());
        default: return "";
    }
}

bool ReqClusterMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    ReqClusterMessage *pp = (ReqClusterMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setEnergy(string2long(value)); return true;
        case 1: pp->setFCH(string2double(value)); return true;
        case 2: pp->setNrMemEvent(string2long(value)); return true;
        default: return false;
    }
}

const char *ReqClusterMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *ReqClusterMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    ReqClusterMessage *pp = (ReqClusterMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(TDMAMessage)

TDMAMessage::TDMAMessage(const char *name, short kind) : ::ClusterMessage(name,kind)
{
    this->frames = 0;
    this->frameTime = 0;
    tdma_arraysize = 0;
    this->tdma = 0;
}

TDMAMessage::TDMAMessage(const TDMAMessage& other) : ::ClusterMessage(other)
{
    tdma_arraysize = 0;
    this->tdma = 0;
    copy(other);
}

TDMAMessage::~TDMAMessage()
{
    delete [] this->tdma;
}

TDMAMessage& TDMAMessage::operator=(const TDMAMessage& other)
{
    if (this==&other) return *this;
    ::ClusterMessage::operator=(other);
    copy(other);
    return *this;
}

void TDMAMessage::copy(const TDMAMessage& other)
{
    this->frames = other.frames;
    this->frameTime = other.frameTime;
    delete [] this->tdma;
    this->tdma = (other.tdma_arraysize==0) ? nullptr : new int[other.tdma_arraysize];
    tdma_arraysize = other.tdma_arraysize;
    for (unsigned int i=0; i<tdma_arraysize; i++)
        this->tdma[i] = other.tdma[i];
}

void TDMAMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::ClusterMessage::parsimPack(b);
    doParsimPacking(b,this->frames);
    doParsimPacking(b,this->frameTime);
    b->pack(tdma_arraysize);
    doParsimArrayPacking(b,this->tdma,tdma_arraysize);
}

void TDMAMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::ClusterMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->frames);
    doParsimUnpacking(b,this->frameTime);
    delete [] this->tdma;
    b->unpack(tdma_arraysize);
    if (tdma_arraysize==0) {
        this->tdma = 0;
    } else {
        this->tdma = new int[tdma_arraysize];
        doParsimArrayUnpacking(b,this->tdma,tdma_arraysize);
    }
}

int TDMAMessage::getFrames() const
{
    return this->frames;
}

void TDMAMessage::setFrames(int frames)
{
    this->frames = frames;
}

int TDMAMessage::getFrameTime() const
{
    return this->frameTime;
}

void TDMAMessage::setFrameTime(int frameTime)
{
    this->frameTime = frameTime;
}

void TDMAMessage::setTdmaArraySize(unsigned int size)
{
    int *tdma2 = (size==0) ? nullptr : new int[size];
    unsigned int sz = tdma_arraysize < size ? tdma_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        tdma2[i] = this->tdma[i];
    for (unsigned int i=sz; i<size; i++)
        tdma2[i] = 0;
    tdma_arraysize = size;
    delete [] this->tdma;
    this->tdma = tdma2;
}

unsigned int TDMAMessage::getTdmaArraySize() const
{
    return tdma_arraysize;
}

int TDMAMessage::getTdma(unsigned int k) const
{
    if (k>=tdma_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", tdma_arraysize, k);
    return this->tdma[k];
}

void TDMAMessage::setTdma(unsigned int k, int tdma)
{
    if (k>=tdma_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", tdma_arraysize, k);
    this->tdma[k] = tdma;
}

class TDMAMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    TDMAMessageDescriptor();
    virtual ~TDMAMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(TDMAMessageDescriptor)

TDMAMessageDescriptor::TDMAMessageDescriptor() : omnetpp::cClassDescriptor("TDMAMessage", "ClusterMessage")
{
    propertynames = nullptr;
}

TDMAMessageDescriptor::~TDMAMessageDescriptor()
{
    delete[] propertynames;
}

bool TDMAMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TDMAMessage *>(obj)!=nullptr;
}

const char **TDMAMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *TDMAMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int TDMAMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int TDMAMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *TDMAMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "frames",
        "frameTime",
        "tdma",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int TDMAMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='f' && strcmp(fieldName, "frames")==0) return base+0;
    if (fieldName[0]=='f' && strcmp(fieldName, "frameTime")==0) return base+1;
    if (fieldName[0]=='t' && strcmp(fieldName, "tdma")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *TDMAMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **TDMAMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *TDMAMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int TDMAMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    TDMAMessage *pp = (TDMAMessage *)object; (void)pp;
    switch (field) {
        case 2: return pp->getTdmaArraySize();
        default: return 0;
    }
}

const char *TDMAMessageDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TDMAMessage *pp = (TDMAMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TDMAMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TDMAMessage *pp = (TDMAMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getFrames());
        case 1: return long2string(pp->getFrameTime());
        case 2: return long2string(pp->getTdma(i));
        default: return "";
    }
}

bool TDMAMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    TDMAMessage *pp = (TDMAMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setFrames(string2long(value)); return true;
        case 1: pp->setFrameTime(string2long(value)); return true;
        case 2: pp->setTdma(i,string2long(value)); return true;
        default: return false;
    }
}

const char *TDMAMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *TDMAMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    TDMAMessage *pp = (TDMAMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(DataToCHMessage)

DataToCHMessage::DataToCHMessage(const char *name, short kind) : ::ClusterMessage(name,kind)
{
    this->clusterHead = 0;
    this->data = 0;
}

DataToCHMessage::DataToCHMessage(const DataToCHMessage& other) : ::ClusterMessage(other)
{
    copy(other);
}

DataToCHMessage::~DataToCHMessage()
{
}

DataToCHMessage& DataToCHMessage::operator=(const DataToCHMessage& other)
{
    if (this==&other) return *this;
    ::ClusterMessage::operator=(other);
    copy(other);
    return *this;
}

void DataToCHMessage::copy(const DataToCHMessage& other)
{
    this->clusterHead = other.clusterHead;
    this->data = other.data;
}

void DataToCHMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::ClusterMessage::parsimPack(b);
    doParsimPacking(b,this->clusterHead);
    doParsimPacking(b,this->data);
}

void DataToCHMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::ClusterMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->clusterHead);
    doParsimUnpacking(b,this->data);
}

int DataToCHMessage::getClusterHead() const
{
    return this->clusterHead;
}

void DataToCHMessage::setClusterHead(int clusterHead)
{
    this->clusterHead = clusterHead;
}

int DataToCHMessage::getData() const
{
    return this->data;
}

void DataToCHMessage::setData(int data)
{
    this->data = data;
}

class DataToCHMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    DataToCHMessageDescriptor();
    virtual ~DataToCHMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(DataToCHMessageDescriptor)

DataToCHMessageDescriptor::DataToCHMessageDescriptor() : omnetpp::cClassDescriptor("DataToCHMessage", "ClusterMessage")
{
    propertynames = nullptr;
}

DataToCHMessageDescriptor::~DataToCHMessageDescriptor()
{
    delete[] propertynames;
}

bool DataToCHMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<DataToCHMessage *>(obj)!=nullptr;
}

const char **DataToCHMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *DataToCHMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int DataToCHMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int DataToCHMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *DataToCHMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "clusterHead",
        "data",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int DataToCHMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "clusterHead")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "data")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *DataToCHMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **DataToCHMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *DataToCHMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int DataToCHMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    DataToCHMessage *pp = (DataToCHMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *DataToCHMessageDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    DataToCHMessage *pp = (DataToCHMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string DataToCHMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    DataToCHMessage *pp = (DataToCHMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getClusterHead());
        case 1: return long2string(pp->getData());
        default: return "";
    }
}

bool DataToCHMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    DataToCHMessage *pp = (DataToCHMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setClusterHead(string2long(value)); return true;
        case 1: pp->setData(string2long(value)); return true;
        default: return false;
    }
}

const char *DataToCHMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *DataToCHMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    DataToCHMessage *pp = (DataToCHMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(ACKRelayMessage)

ACKRelayMessage::ACKRelayMessage(const char *name, short kind) : ::ClusterMessage(name,kind)
{
    this->energy = 0;
    this->distBS = 0;
    this->status = 0;
    this->xpos = 0;
    this->ypos = 0;
}

ACKRelayMessage::ACKRelayMessage(const ACKRelayMessage& other) : ::ClusterMessage(other)
{
    copy(other);
}

ACKRelayMessage::~ACKRelayMessage()
{
}

ACKRelayMessage& ACKRelayMessage::operator=(const ACKRelayMessage& other)
{
    if (this==&other) return *this;
    ::ClusterMessage::operator=(other);
    copy(other);
    return *this;
}

void ACKRelayMessage::copy(const ACKRelayMessage& other)
{
    this->energy = other.energy;
    this->distBS = other.distBS;
    this->status = other.status;
    this->xpos = other.xpos;
    this->ypos = other.ypos;
}

void ACKRelayMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::ClusterMessage::parsimPack(b);
    doParsimPacking(b,this->energy);
    doParsimPacking(b,this->distBS);
    doParsimPacking(b,this->status);
    doParsimPacking(b,this->xpos);
    doParsimPacking(b,this->ypos);
}

void ACKRelayMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::ClusterMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->energy);
    doParsimUnpacking(b,this->distBS);
    doParsimUnpacking(b,this->status);
    doParsimUnpacking(b,this->xpos);
    doParsimUnpacking(b,this->ypos);
}

int ACKRelayMessage::getEnergy() const
{
    return this->energy;
}

void ACKRelayMessage::setEnergy(int energy)
{
    this->energy = energy;
}

int ACKRelayMessage::getDistBS() const
{
    return this->distBS;
}

void ACKRelayMessage::setDistBS(int distBS)
{
    this->distBS = distBS;
}

int ACKRelayMessage::getStatus() const
{
    return this->status;
}

void ACKRelayMessage::setStatus(int status)
{
    this->status = status;
}

int ACKRelayMessage::getXpos() const
{
    return this->xpos;
}

void ACKRelayMessage::setXpos(int xpos)
{
    this->xpos = xpos;
}

int ACKRelayMessage::getYpos() const
{
    return this->ypos;
}

void ACKRelayMessage::setYpos(int ypos)
{
    this->ypos = ypos;
}

class ACKRelayMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    ACKRelayMessageDescriptor();
    virtual ~ACKRelayMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(ACKRelayMessageDescriptor)

ACKRelayMessageDescriptor::ACKRelayMessageDescriptor() : omnetpp::cClassDescriptor("ACKRelayMessage", "ClusterMessage")
{
    propertynames = nullptr;
}

ACKRelayMessageDescriptor::~ACKRelayMessageDescriptor()
{
    delete[] propertynames;
}

bool ACKRelayMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ACKRelayMessage *>(obj)!=nullptr;
}

const char **ACKRelayMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *ACKRelayMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int ACKRelayMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount() : 5;
}

unsigned int ACKRelayMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *ACKRelayMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "energy",
        "distBS",
        "status",
        "xpos",
        "ypos",
    };
    return (field>=0 && field<5) ? fieldNames[field] : nullptr;
}

int ACKRelayMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='e' && strcmp(fieldName, "energy")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "distBS")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "status")==0) return base+2;
    if (fieldName[0]=='x' && strcmp(fieldName, "xpos")==0) return base+3;
    if (fieldName[0]=='y' && strcmp(fieldName, "ypos")==0) return base+4;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *ACKRelayMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : nullptr;
}

const char **ACKRelayMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *ACKRelayMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int ACKRelayMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    ACKRelayMessage *pp = (ACKRelayMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *ACKRelayMessageDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ACKRelayMessage *pp = (ACKRelayMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ACKRelayMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ACKRelayMessage *pp = (ACKRelayMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getEnergy());
        case 1: return long2string(pp->getDistBS());
        case 2: return long2string(pp->getStatus());
        case 3: return long2string(pp->getXpos());
        case 4: return long2string(pp->getYpos());
        default: return "";
    }
}

bool ACKRelayMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    ACKRelayMessage *pp = (ACKRelayMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setEnergy(string2long(value)); return true;
        case 1: pp->setDistBS(string2long(value)); return true;
        case 2: pp->setStatus(string2long(value)); return true;
        case 3: pp->setXpos(string2long(value)); return true;
        case 4: pp->setYpos(string2long(value)); return true;
        default: return false;
    }
}

const char *ACKRelayMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *ACKRelayMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    ACKRelayMessage *pp = (ACKRelayMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(Data2BSMessage)

Data2BSMessage::Data2BSMessage(const char *name, short kind) : ::ClusterMessage(name,kind)
{
    this->data = 0;
}

Data2BSMessage::Data2BSMessage(const Data2BSMessage& other) : ::ClusterMessage(other)
{
    copy(other);
}

Data2BSMessage::~Data2BSMessage()
{
}

Data2BSMessage& Data2BSMessage::operator=(const Data2BSMessage& other)
{
    if (this==&other) return *this;
    ::ClusterMessage::operator=(other);
    copy(other);
    return *this;
}

void Data2BSMessage::copy(const Data2BSMessage& other)
{
    this->data = other.data;
}

void Data2BSMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::ClusterMessage::parsimPack(b);
    doParsimPacking(b,this->data);
}

void Data2BSMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::ClusterMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->data);
}

int Data2BSMessage::getData() const
{
    return this->data;
}

void Data2BSMessage::setData(int data)
{
    this->data = data;
}

class Data2BSMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    Data2BSMessageDescriptor();
    virtual ~Data2BSMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(Data2BSMessageDescriptor)

Data2BSMessageDescriptor::Data2BSMessageDescriptor() : omnetpp::cClassDescriptor("Data2BSMessage", "ClusterMessage")
{
    propertynames = nullptr;
}

Data2BSMessageDescriptor::~Data2BSMessageDescriptor()
{
    delete[] propertynames;
}

bool Data2BSMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Data2BSMessage *>(obj)!=nullptr;
}

const char **Data2BSMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *Data2BSMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int Data2BSMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int Data2BSMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *Data2BSMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "data",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int Data2BSMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "data")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *Data2BSMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **Data2BSMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *Data2BSMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int Data2BSMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Data2BSMessage *pp = (Data2BSMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *Data2BSMessageDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Data2BSMessage *pp = (Data2BSMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Data2BSMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Data2BSMessage *pp = (Data2BSMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getData());
        default: return "";
    }
}

bool Data2BSMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Data2BSMessage *pp = (Data2BSMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setData(string2long(value)); return true;
        default: return false;
    }
}

const char *Data2BSMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *Data2BSMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Data2BSMessage *pp = (Data2BSMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


