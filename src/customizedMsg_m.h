//
// Generated file, do not edit! Created by nedtool 5.6 from customizedMsg.msg.
//

#ifndef __CUSTOMIZEDMSG_M_H
#define __CUSTOMIZEDMSG_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0506
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
#include <bitset>
typedef  std::bitset<8> bits;  
// }}

/**
 * Class generated from <tt>customizedMsg.msg:25</tt> by nedtool.
 * <pre>
 * packet CustomizedMsg
 * {
 *     \@customize(true);  // see the generated C++ header for more info
 *     int seq_num; // header
 *     int frame_type; // : Data=0, ACK=1, NACK=2
 *     string msg_payload; //frame after byte stuffing
 *     int n_ack_value; // value for acknowledgement if frame type is ack or nack
 *     char mycheckbits; //trailer
 * }
 * </pre>
 *
 * CustomizedMsg_Base is only useful if it gets subclassed, and CustomizedMsg is derived from it.
 * The minimum code to be written for CustomizedMsg is the following:
 *
 * <pre>
 * class CustomizedMsg : public CustomizedMsg_Base
 * {
 *   private:
 *     void copy(const CustomizedMsg& other) { ... }

 *   public:
 *     CustomizedMsg(const char *name=nullptr, short kind=0) : CustomizedMsg_Base(name,kind) {}
 *     CustomizedMsg(const CustomizedMsg& other) : CustomizedMsg_Base(other) {copy(other);}
 *     CustomizedMsg& operator=(const CustomizedMsg& other) {if (this==&other) return *this; CustomizedMsg_Base::operator=(other); copy(other); return *this;}
 *     virtual CustomizedMsg *dup() const override {return new CustomizedMsg(*this);}
 *     // ADD CODE HERE to redefine and implement pure virtual functions from CustomizedMsg_Base
 * };
 * </pre>
 *
 * The following should go into a .cc (.cpp) file:
 *
 * <pre>
 * Register_Class(CustomizedMsg)
 * </pre>
 */
class CustomizedMsg_Base : public ::omnetpp::cPacket
{
  protected:
    int seq_num;
    int frame_type;
    ::omnetpp::opp_string msg_payload;
    int n_ack_value;
    char mycheckbits;

  private:
    void copy(const CustomizedMsg_Base& other);

  public:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const CustomizedMsg_Base&);
    // make constructors protected to avoid instantiation
    CustomizedMsg_Base(const char *name=nullptr, short kind=0);
    CustomizedMsg_Base(const CustomizedMsg_Base& other);
    // make assignment operator protected to force the user override it
    CustomizedMsg_Base& operator=(const CustomizedMsg_Base& other);

  public:
    virtual ~CustomizedMsg_Base();
    virtual CustomizedMsg_Base *dup() const override {
        //throw omnetpp::cRuntimeError("You forgot to manually add a dup() function to class CustomizedMsg");

        return new CustomizedMsg_Base(*this);
    }
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getSeq_num() const;
    virtual void setSeq_num(int seq_num);
    virtual int getFrame_type() const;
    virtual void setFrame_type(int frame_type);
    virtual const char * getMsg_payload() const;
    virtual void setMsg_payload(const char * msg_payload);
    virtual int getN_ack_value() const;
    virtual void setN_ack_value(int n_ack_value);
    virtual char getMycheckbits() const;
    virtual void setMycheckbits(char mycheckbits);
};


#endif // ifndef __CUSTOMIZEDMSG_M_H

