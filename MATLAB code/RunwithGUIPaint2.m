function[coordinate]=RunwithGUIPaint2(cam)
global vidh vidw state_red P_red gamma1 upperx lowerx value brightfactor paint tempimg;
tempimg=snapshot(cam);
tempimg=flip(tempimg,2);
[xred,yred]=CallObjectTrackwithGUI(vidh,vidw,cam,value,brightfactor,gamma1,upperx,lowerx);
sensorreading=[xred;yred];
[state_red,P_red]=KalmanFilterRun(0.005,state_red,P_red,sensorreading);
tempimg=insertShape(tempimg,'circle',[round(state_red(1)),round(state_red(2)),5],'LineWidth',3,'Color','red');
coordinate=state_red;
scoordinate=coordinate;
if(coordinate(2)==0)
    scoordinate(2)=1;
end
if(coordinate(1)==0)
    scoordinate(1)=1;
end
paint(floor(scoordinate(2)),floor(scoordinate(1)))=1;
end