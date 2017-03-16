#ifndef _ROS_cob_msgs_EmergencyStopState_h
#define _ROS_cob_msgs_EmergencyStopState_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace cob_msgs
{

  class EmergencyStopState : public ros::Msg
  {
    public:
      bool emergency_button_stop;
      bool scanner_stop;
      int16_t emergency_state;
      enum { EMFREE =  0 		 };
      enum { EMSTOP =  1 		 };
      enum { EMCONFIRMED =  2 	 };

    EmergencyStopState():
      emergency_button_stop(0),
      scanner_stop(0),
      emergency_state(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_emergency_button_stop;
      u_emergency_button_stop.real = this->emergency_button_stop;
      *(outbuffer + offset + 0) = (u_emergency_button_stop.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->emergency_button_stop);
      union {
        bool real;
        uint8_t base;
      } u_scanner_stop;
      u_scanner_stop.real = this->scanner_stop;
      *(outbuffer + offset + 0) = (u_scanner_stop.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->scanner_stop);
      union {
        int16_t real;
        uint16_t base;
      } u_emergency_state;
      u_emergency_state.real = this->emergency_state;
      *(outbuffer + offset + 0) = (u_emergency_state.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_emergency_state.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->emergency_state);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_emergency_button_stop;
      u_emergency_button_stop.base = 0;
      u_emergency_button_stop.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->emergency_button_stop = u_emergency_button_stop.real;
      offset += sizeof(this->emergency_button_stop);
      union {
        bool real;
        uint8_t base;
      } u_scanner_stop;
      u_scanner_stop.base = 0;
      u_scanner_stop.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->scanner_stop = u_scanner_stop.real;
      offset += sizeof(this->scanner_stop);
      union {
        int16_t real;
        uint16_t base;
      } u_emergency_state;
      u_emergency_state.base = 0;
      u_emergency_state.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_emergency_state.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->emergency_state = u_emergency_state.real;
      offset += sizeof(this->emergency_state);
     return offset;
    }

    const char * getType(){ return "cob_msgs/EmergencyStopState"; };
    const char * getMD5(){ return "d857d7312ffc16f75239036504e493e9"; };

  };

}
#endif