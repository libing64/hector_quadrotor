//=================================================================================================
// Copyright (c) 2013, Johannes Meyer, TU Darmstadt
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the Flight Systems and Automatic Control group,
//       TU Darmstadt, nor the names of its contributors may be used to
//       endorse or promote products derived from this software without
//       specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//=================================================================================================

#ifndef HECTOR_QUADROTOR_CONTROLLER_QUADROTOR_HARDWARE_GAZEBO_H
#define HECTOR_QUADROTOR_CONTROLLER_QUADROTOR_HARDWARE_GAZEBO_H

#include <gazebo_ros_control/robot_hw_sim.h>
#include <hector_quadrotor_controller/quadrotor_interface.h>

#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Imu.h>
#include <geometry_msgs/Wrench.h>
#include <hector_uav_msgs/MotorCommand.h>
#include <nav_msgs/Path.h>

#include <ros/node_handle.h>

namespace hector_quadrotor_controller {

using namespace hardware_interface;
using namespace gazebo_ros_control;

class QuadrotorHardwareSim : public RobotHWSim, public QuadrotorInterface
{
public:
  QuadrotorHardwareSim();
  virtual ~QuadrotorHardwareSim();

  virtual bool initSim(
      ros::NodeHandle model_nh,
      gazebo::physics::ModelPtr parent_model,
      std::vector<transmission_interface::TransmissionInfo> transmissions);

  virtual void readSim(ros::Time time, ros::Duration period);

  virtual void writeSim(ros::Time time, ros::Duration period);

protected:
  geometry_msgs::Pose pose_;
  geometry_msgs::Twist twist_;
  sensor_msgs::Imu imu_;
  hector_uav_msgs::MotorStatus motor_status_;

  geometry_msgs::Pose pose_command_;
  geometry_msgs::Twist twist_command_;
  geometry_msgs::Wrench wrench_command_;
  hector_uav_msgs::MotorCommand motor_command_;
  nav_msgs::Path trajectory_command_;

  gazebo::physics::ModelPtr parent_model;

  ros::Subscriber stateSubscriber;
  ros::Publisher commandVelocityPublisher;
  ros::Publisher wrenchPublisher;
};

} // namespace hector_quadrotor_controller

#endif // HECTOR_QUADROTOR_CONTROLLER_QUADROTOR_HARDWARE_GAZEBO_H
