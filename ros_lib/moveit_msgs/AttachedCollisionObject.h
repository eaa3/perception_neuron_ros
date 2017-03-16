#ifndef _ROS_moveit_msgs_AttachedCollisionObject_h
#define _ROS_moveit_msgs_AttachedCollisionObject_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "moveit_msgs/CollisionObject.h"
#include "trajectory_msgs/JointTrajectory.h"

namespace moveit_msgs
{

  class AttachedCollisionObject : public ros::Msg
  {
    public:
      const char* link_name;
      moveit_msgs::CollisionObject object;
      uint8_t touch_links_length;
      char* st_touch_links;
      char* * touch_links;
      trajectory_msgs::JointTrajectory detach_posture;
      double weight;

    AttachedCollisionObject():
      link_name(""),
      object(),
      touch_links_length(0), touch_links(NULL),
      detach_posture(),
      weight(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_link_name = strlen(this->link_name);
      memcpy(outbuffer + offset, &length_link_name, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->link_name, length_link_name);
      offset += length_link_name;
      offset += this->object.serialize(outbuffer + offset);
      *(outbuffer + offset++) = touch_links_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < touch_links_length; i++){
      uint32_t length_touch_linksi = strlen(this->touch_links[i]);
      memcpy(outbuffer + offset, &length_touch_linksi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->touch_links[i], length_touch_linksi);
      offset += length_touch_linksi;
      }
      offset += this->detach_posture.serialize(outbuffer + offset);
      union {
        double real;
        uint64_t base;
      } u_weight;
      u_weight.real = this->weight;
      *(outbuffer + offset + 0) = (u_weight.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_weight.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_weight.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_weight.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_weight.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_weight.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_weight.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_weight.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->weight);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_link_name;
      memcpy(&length_link_name, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_link_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_link_name-1]=0;
      this->link_name = (char *)(inbuffer + offset-1);
      offset += length_link_name;
      offset += this->object.deserialize(inbuffer + offset);
      uint8_t touch_links_lengthT = *(inbuffer + offset++);
      if(touch_links_lengthT > touch_links_length)
        this->touch_links = (char**)realloc(this->touch_links, touch_links_lengthT * sizeof(char*));
      offset += 3;
      touch_links_length = touch_links_lengthT;
      for( uint8_t i = 0; i < touch_links_length; i++){
      uint32_t length_st_touch_links;
      memcpy(&length_st_touch_links, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_touch_links; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_touch_links-1]=0;
      this->st_touch_links = (char *)(inbuffer + offset-1);
      offset += length_st_touch_links;
        memcpy( &(this->touch_links[i]), &(this->st_touch_links), sizeof(char*));
      }
      offset += this->detach_posture.deserialize(inbuffer + offset);
      union {
        double real;
        uint64_t base;
      } u_weight;
      u_weight.base = 0;
      u_weight.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_weight.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_weight.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_weight.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_weight.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_weight.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_weight.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_weight.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->weight = u_weight.real;
      offset += sizeof(this->weight);
     return offset;
    }

    const char * getType(){ return "moveit_msgs/AttachedCollisionObject"; };
    const char * getMD5(){ return "3ceac60b21e85bbd6c5b0ab9d476b752"; };

  };

}
#endif