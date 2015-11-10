function[coordinate,paint]=RunwithGUIPaint(cam,paint,l_coordinate)
global vidh vidw state_red P_red gamma1 upperx lowerx value brightfactor;
tempimg=snapshot(cam);
[xred,yred]=CallObjectTrackwithGUI(vidh,vidw,cam,value,brightfactor,gamma1,upperx,lowerx);
sensorreading=[xred;yred];
[state_red,P_red]=KalmanFilterRun(0.005,state_red,P_red,sensorreading);
tempimg=insertShape(tempimg,'circle',[round(state_red(1)),round(state_red(2)),5],'LineWidth',3,'Color','red');
coordinate=state_red;
sendcoordinate=[coordinate(1),coordinate(2)];
sendl_coordinate=[l_coordinate(1),l_coordinate(2)];
paint=CreateLine(sendl_coordinate,sendcoordinate,paint);
imshowpair(tempimg,paint,'montage');
end