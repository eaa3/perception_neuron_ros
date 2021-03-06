#ifndef _ROS_SERVICE_GetCartesianPath_h
#define _ROS_SERVICE_GetCartesianPath_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "moveit_msgs/RobotTrajectory.h"
#include "moveit_msgs/RobotState.h"
#include "moveit_msgs/MoveItErrorCodes.h"
#include "geometry_msgs/Pose.h"
#include "moveit_msgs/Constraints.h"

namespace moveit_msgs
{

static const char GETCARTESIANPATH[] = "moveit_msgs/GetCartesianPath";

  class GetCartesianPathRequest : public ros::Msg
  {
    public:
      std_msgs::Header header;
      moveit_msgs::RobotState start_state;
      const char* group_name;
      const char* link_name;
      uint8_t waypoints_length;
      geometry_msgs::Pose st_waypoints;
      geometry_msgs::Pose * waypoints;
      double max_step;
      double jump_threshold;
      bool avoid_collisions;
      moveit_msgs::Constraints path_constraints;

    GetCartesianPathRequest():
      header(),
      start_state(),
      group_name(""),
      link_name(""),
      waypoints_length(0), waypoints(NULL),
      max_step(0),
      jump_threshold(0),
      avoid_collisions(0),
      path_constraints()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->start_state.serialize(outbuffer + offset);
      uint32_t length_group_name = strlen(this->group_name);
      memcpy(outbuffer + offset, &length_group_name, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->group_name, length_group_name);
      offset += length_group_name;
      uint32_t length_link_name = strlen(this->link_name);
      memcpy(outbuffer + offset, &length_link_name, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->link_name, length_link_name);
      offset += length_link_name;
      *(outbuffer + offset++) = waypoints_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < waypoints_length; i++){
      offset += this->waypoints[i].serialize(outbuffer + offset);
      }
      union {
        double real;
        uint64_t base;
      } u_max_step;
      u_max_step.real = this->max_step;
      *(outbuffer + offset + 0) = (u_max_step.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_max_step.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_max_step.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_max_step.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_max_step.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_max_step.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_max_step.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_max_step.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->max_step);
      union {
        double real;
        uint64_t base;
      } u_jump_threshold;
      u_jump_threshold.real = this->jump_threshold;
      *(outbuffer + offset + 0) = (u_jump_threshold.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_jump_threshold.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_jump_threshold.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_jump_threshold.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_jump_threshold.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_jump_threshold.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_jump_threshold.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_jump_threshold.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->jump_threshold);
      union {
        bool real;
        uint8_t base;
      } u_avoid_collisions;
      u_avoid_collisions.real = this->avoid_collisions;
      *(outbuffer + offset + 0) = (u_avoid_collisions.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->avoid_collisions);
      offset += this->path_constraints.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->start_state.deserialize(inbuffer + offset);
      uint32_t length_group_name;
      memcpy(&length_group_name, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_group_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_group_name-1]=0;
      this->group_name = (char *)(inbuffer + offset-1);
      offset += length_group_name;
      uint32_t length_link_name;
      memcpy(&length_link_name, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_link_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_link_name-1]=0;
      this->link_name = (char *)(inbuffer + offset-1);
      offset += length_link_name;
      uint8_t waypoints_lengthT = *(inbuffer + offset++);
      if(waypoints_lengthT > waypoints_length)
        this->waypoints = (geometry_msgs::Pose*)realloc(this->waypoints, waypoints_lengthT * sizeof(geometry_msgs::Pose));
      offset += 3;
      waypoints_length = waypoints_lengthT;
      for( uint8_t i = 0; i < waypoints_length; i++){
      offset += this->st_waypoints.deserialize(inbuffer + offset);
        memcpy( &(this->waypoints[i]), &(this->st_waypoints), sizeof(geometry_msgs::Pose));
      }
      union {
        double real;
        uint64_t base;
      } u_max_step;
      u_max_step.base = 0;
      u_max_step.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_max_step.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_max_step.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_max_step.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_max_step.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_max_step.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_max_step.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_max_step.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->max_step = u_max_step.real;
      offset += sizeof(this->max_step);
      union {
        double real;
        uint64_t base;
      } u_jump_threshold;
      u_jump_threshold.base = 0;
      u_jump_threshold.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_jump_threshold.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_jump_threshold.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_jump_threshold.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_jump_threshold.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_jump_threshold.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_jump_threshold.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_jump_threshold.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->jump_threshold = u_jump_threshold.real;
      offset += sizeof(this->jump_threshold);
      union {
        bool real;
        uint8_t base;
      } u_avoid_collisions;
      u_avoid_collisions.base = 0;
      u_avoid_collisions.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->avoid_collisions = u_avoid_collisions.real;
      offset += sizeof(this->avoid_collisions);
      offset += this->path_constraints.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return GETCARTESIANPATH; };
    const char * getMD5(){ return "b37c16ad7ed838d811a270a8054276b6"; };

  };

  class GetCartesianPathResponse : public ros::Msg
  {
    public:
      moveit_msgs::RobotState start_state;
      moveit_msgs::RobotTrajectory solution;
      double fraction;
      moveit_msgs::MoveItErrorCodes error_code;

    GetCartesianPathResponse():
      start_state(),
      solution(),
      fraction(0),
      error_code()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->start_state.serialize(outbuffer + offset);
      offset += this->solution.serialize(outbuffer + offset);
      union {
        double real;
        uint64_t base;
      } u_fraction;
      u_fraction.real = this->fraction;
      *(outbuffer + offset + 0) = (u_fraction.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_fraction.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_fraction.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_fraction.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_fraction.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_fraction.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_fraction.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_fraction.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->fraction);
      offset += this->error_code.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->start_state.deserialize(inbuffer + offset);
      offset += this->solution.deserialize(inbuffer + offset);
      union {
        double real;
        uint64_t base;
      } u_fraction;
      u_fraction.base = 0;
      u_fraction.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_fraction.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_fraction.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_fraction.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_fraction.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_fraction.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_fraction.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_fraction.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->fraction = u_fraction.real;
      offset += sizeof(this->fraction);
      offset += this->error_code.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return GETCARTESIANPATH; };
    const char * getMD5(){ return "45414110461a45eb0e273e013924ce59"; };

  };

  class GetCartesianPath {
    public:
    typedef GetCartesianPathRequest Request;
    typedef GetCartesianPathResponse Response;
  };

}
#endif
