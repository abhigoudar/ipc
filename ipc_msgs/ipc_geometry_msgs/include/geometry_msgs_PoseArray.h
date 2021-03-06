#ifndef __IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_POSE_ARRAY__
#define __IPC_BRIDGE_MATLAB_GEOMETRY_MSGS_POSE_ARRAY__
#include <ipc_bridge_matlab/ipc_bridge_matlab.h>
#include <ipc_bridge/msgs/geometry_msgs_PoseArray.h>

#include <roslib_Header.h>
#include <geometry_msgs_Pose.h>

namespace ipc_bridge_matlab
{
  namespace geometry_msgs
  {
    namespace PoseArray
    {
      static mxArray* ProcessMessage(const ipc_bridge::geometry_msgs::PoseArray &msg)
      {
        const char *fields[] = {"header", "poses"};
        const int nfields = sizeof(fields)/sizeof(*fields);
        mxArray *out = mxCreateStructMatrix(1, 1, nfields, fields);
        
        mxSetField(out, 0, "header", 
                   ipc_bridge_matlab::Header::ProcessMessage(msg.header));

        const int length = msg.poses_length;      
        mxArray *poses = mxCreateCellArray(1, &length);
        for (unsigned int i = 0; i < length; i++)
          mxSetCell(poses, i, 
                    ipc_bridge_matlab::geometry_msgs::Pose::ProcessMessage(msg.poses[i]));
        mxSetField(out, 0, "poses", poses);
                
        return out;
      }
      
      static int ProcessArray(const mxArray *a, 
                              ipc_bridge::geometry_msgs::PoseArray &msg)
      {
        mxArray *field;

        field = mxGetField(a, 0, "header");
        ipc_bridge_matlab::Header::ProcessArray(field, msg.header);
        
        field = mxGetField(a, 0, "poses");
        int nrows = mxGetM(field);
        int ncols = mxGetN(field);

        unsigned int length = nrows;
        if (nrows < ncols)
          length = ncols;
        msg.poses_length = length;

        if ((ncols == 0) || (nrows == 0))
          {
            msg.poses_length = 0;
            msg.poses = 0;
          }

        if (msg.poses_length > 0)
          {
            msg.poses = new geometry_msgs_Pose[msg.poses_length];
            for (unsigned int i = 0; i < msg.poses_length; i++)
              {
                mxArray *p = mxGetCell(field, i);
                ipc_bridge_matlab::geometry_msgs::Pose::ProcessArray(p, msg.poses[i]);
              }
          }
        
        return SUCCESS;
      }

      static void Cleanup(ipc_bridge::geometry_msgs::PoseArray &msg)
      {
        ipc_bridge_matlab::Header::Cleanup(msg.header);
        for (unsigned int i = 0; i < msg.poses_length; i++)
          ipc_bridge_matlab::geometry_msgs::Pose::Cleanup(msg.poses[i]);
        if (msg.poses != 0)
          {
            delete[] msg.poses;
            msg.poses_length = 0;
            msg.poses = 0;
          }
      }
    }
  }
}
#endif
