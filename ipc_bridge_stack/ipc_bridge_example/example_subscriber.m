% IPC-Bridge Example Subscriber
% 1/24/2011
% Ben Cohen
clear all;
clc;

% aeedd the ipc_bridge_matlab binaries to your path
[a, p] = system('rospack find ipc_geometry_msgs');
addpath(strcat(p, '/bin')); 

% create a publisher that publishes a geometry_msgs/Twist message
pid=geometry_msgs_Twist('connect','subscriber','example_module','twist');

% create an empty geometry_msgs/Twist message structure
msg=geometry_msgs_Twist('empty');

% read a message and print to screen
while (1)
    msg = geometry_msgs_Twist('read',pid,100);
    msg.linear.x
    msg.linear.y
    msg.linear.z
end
