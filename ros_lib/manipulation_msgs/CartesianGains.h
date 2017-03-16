#ifndef _ROS_manipulation_msgs_CartesianGains_h
#define _ROS_manipulation_msgs_CartesianGains_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace manipulation_msgs
{

  class CartesianGains : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t gains_length;
      double st_gains;
      double * gains;
      uint8_t fixed_frame_length;
      double st_fixed_frame;
      double * fixed_frame;

    CartesianGains():
      header(),
      gains_length(0), gains(NULL),
      fixed_frame_length(0), fixed_frame(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset++) = gains_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < gains_length; i++){
      union {
        double real;
        uint64_t base;
      } u_gainsi;
      u_gainsi.real = this->gains[i];
      *(outbuffer + offset + 0) = (u_gainsi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_gainsi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_gainsi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_gainsi.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_gainsi.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_gainsi.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_gainsi.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_gainsi.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->gains[i]);
      }
      *(outbuffer + offset++) = fixed_frame_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < fixed_frame_length; i++){
      union {
        double real;
        uint64_t base;
      } u_fixed_framei;
      u_fixed_framei.real = this->fixed_frame[i];
      *(outbuffer + offset + 0) = (u_fixed_framei.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_fixed_framei.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_fixed_framei.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_fixed_framei.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_fixed_framei.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_fixed_framei.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_fixed_framei.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_fixed_framei.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->fixed_frame[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint8_t gains_lengthT = *(inbuffer + offset++);
      if(gains_lengthT > gains_length)
        this->gains = (double*)realloc(this->gains, gains_lengthT * sizeof(double));
      offset += 3;
      gains_length = gains_lengthT;
      for( uint8_t i = 0; i < gains_length; i++){
      union {
        double real;
        uint64_t base;
      } u_st_gains;
      u_st_gains.base = 0;
      u_st_gains.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_gains.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_gains.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_gains.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_st_gains.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_st_gains.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_st_gains.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_st_gains.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->st_gains = u_st_gains.real;
      offset += sizeof(this->st_gains);
        memcpy( &(this->gains[i]), &(this->st_gains), sizeof(double));
      }
      uint8_t fixed_frame_lengthT = *(inbuffer + offset++);
      if(fixed_frame_lengthT > fixed_frame_length)
        this->fixed_frame = (double*)realloc(this->fixed_frame, fixed_frame_lengthT * sizeof(double));
      offset += 3;
      fixed_frame_length = fixed_frame_lengthT;
      for( uint8_t i = 0; i < fixed_frame_length; i++){
      union {
        double real;
        uint64_t base;
      } u_st_fixed_frame;
      u_st_fixed_frame.base = 0;
      u_st_fixed_frame.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_fixed_frame.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_fixed_frame.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_fixed_frame.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_st_fixed_frame.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_st_fixed_frame.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_st_fixed_frame.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_st_fixed_frame.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->st_fixed_frame = u_st_fixed_frame.real;
      offset += sizeof(this->st_fixed_frame);
        memcpy( &(this->fixed_frame[i]), &(this->st_fixed_frame), sizeof(double));
      }
     return offset;
    }

    const char * getType(){ return "manipulation_msgs/CartesianGains"; };
    const char * getMD5(){ return "ab347f046ca5736a156ec424cbb63635"; };

  };

}
#endif