#ifndef HAL_HW_INTERFACE_HAL_HW_INTERFACE_H
#define HAL_HW_INTERFACE_HAL_HW_INTERFACE_H

// hal_hw_interface subclasses ros_control_boilerplate
#include <ros_control_boilerplate/generic_hw_interface.h>

// HAL
#include <hal.h>

// ROS
#include <ros/duration.h>

// Component name
#define CNAME "hal_hw_interface"

namespace hal_hw_interface
{
class HalHWInterface : public ros_control_boilerplate::GenericHWInterface
{
public:
  /**
   * \brief Constructor
   * \param nh - ROS node handle
   * \param urdf_model - optional pointer to a parsed robot model
   */

  HalHWInterface(ros::NodeHandle& nh, urdf::Model* urdf_model = NULL);

  /**
   * \brief Initialize the hardware interface
   * \param funct - the component function run periodically in a HAL RT thread
   */
  void init(void (*funct)(void*, long));

  /**
   * \brief Create float-type HAL pin
   * \param ix - pin
   * \param ptrs - a vector of double pointers to HAL float storage
   * \param dir - pin direction; one of HAL_IN, HAL_OUT
   * \param func - the HAL component function that runs read/update/write
   */
  bool create_float_pin(const std::size_t ix, std::vector<double**>* ptrs, hal_pin_dir_t dir, const char* func);

  /**
   * \brief Read the state from the robot hardware.
   * \param elapsed_time - period since last run
   */
  void read(ros::Duration& elapsed_time);

  /**
   * \brief Write the command to the robot hardware.
   * \param elapsed_time - period since last run
   */
  void write(ros::Duration& elapsed_time);

  /**
   * \brief Enforce joint limits
   * \param elapsed_time - period since last run
   */
  void enforceLimits(ros::Duration& period);

  /**
   * \brief Shut down the HAL component and the ROS node
   */
  void shutdown();

protected:
  /**
   * \brief HAL component ID
   */
  int comp_id_;

private:
  // Joints:  HAL storage
  // - Commands
  std::vector<double**> joint_pos_cmd_ptrs_;
  std::vector<double**> joint_vel_cmd_ptrs_;
  std::vector<double**> joint_eff_cmd_ptrs_;
  // - States
  std::vector<double**> joint_pos_fb_ptrs_;
  std::vector<double**> joint_vel_fb_ptrs_;
  std::vector<double**> joint_eff_fb_ptrs_;

};  // HalHWInterface

}  // hardware_interface

#endif  // HAL_HW_INTERFACE_HAL_HW_INTERFACE_H
