//
// Generated file, do not edit! Created by opp_msgtool 6.0 from NodeMsg.msg.
//

#ifndef __NODEMSG_M_H
#define __NODEMSG_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0600
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif

class NodeMsg;
/**
 * Class generated from <tt>NodeMsg.msg:30</tt> by opp_msgtool.
 * <pre>
 * //
 * // TODO generated message class
 * //
 * packet NodeMsg
 * {
 *     //    SomeType field1;
 *     //    OtherType field2;
 *     int seq_num;
 *     string payload;
 *     char parityByte;
 *     int messageType; // data = 0, ack = 1, nack = 2
 *     int ack_num;
 * }
 * </pre>
 */
class NodeMsg : public ::omnetpp::cPacket
{
  protected:
    int seq_num = 0;
    omnetpp::opp_string payload;
    char parityByte = 0;
    int messageType = 0;
    int ack_num = 0;

  private:
    void copy(const NodeMsg& other);

  protected:
    bool operator==(const NodeMsg&) = delete;

  public:
    NodeMsg(const char *name=nullptr, short kind=0);
    NodeMsg(const NodeMsg& other);
    virtual ~NodeMsg();
    NodeMsg& operator=(const NodeMsg& other);
    virtual NodeMsg *dup() const override {return new NodeMsg(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual int getSeq_num() const;
    virtual void setSeq_num(int seq_num);

    virtual const char * getPayload() const;
    virtual void setPayload(const char * payload);

    virtual char getParityByte() const;
    virtual void setParityByte(char parityByte);

    virtual int getMessageType() const;
    virtual void setMessageType(int messageType);

    virtual int getAck_num() const;
    virtual void setAck_num(int ack_num);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const NodeMsg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, NodeMsg& obj) {obj.parsimUnpack(b);}


namespace omnetpp {

template<> inline NodeMsg *fromAnyPtr(any_ptr ptr) { return check_and_cast<NodeMsg*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __NODEMSG_M_H

