global state_red state_blue P_red P_blue Ex vidh vidw; 
vidh = 160;
vidw = 120; 
KalmanFilterInit(); 
P_red=Ex; 
P_blue=Ex;
state_red=[0;0;0;0]; 
state_blue=[0;0;0;0];