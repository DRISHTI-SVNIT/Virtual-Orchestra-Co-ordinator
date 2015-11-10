function[xred,yred]=CallObjectTrackwithGUI(vidh,vidw,cam,value,brightfactor,gamma2,upper,lower)
    SE=strel('disk',3);
    SE1=strel('disk',2);
    s=zeros(vidh,vidw);
    s=snapshot(cam);
    tempimg=flip(s,2);
    tempimg=brightfactor*100+tempimg;
    for i=1:3
    tempimg(:,:,i)=imadjust(tempimg(:,:,i),[],[],gamma2);
    end
    r=tempimg(:,:,1);
    g=tempimg(:,:,2);
    b=tempimg(:,:,3);
    red_tempr=r>value(1) & r<value(2);
    red_tempg=g>value(3) & g<value(4);
    red_tempb=b>value(5) & b<value(6);
    red_img=red_tempr & red_tempg & red_tempb;
    
    red_img=imdilate(red_img,SE1);
    
    %Perform Connected Component Analysis and filter the noises.
    %red_connComp=bwconncomp(red_img);
    %red_stats=regionprops(red_connComp,'Area');
    red_mask=red_img;
    %red_mask(vertcat(red_connComp.PixelIdxList{[red_stats.Area]<lower | [red_stats.Area]>upper}))=0;
    
    %Some morphological operations for smoothing the segmented object.
    red_mask=imdilate(red_mask,SE);
    
    %Find C.M. of binary object.
    [red_x,red_y]=find(red_mask);
    
    if ~isempty(red_x)
        red_C(1,:)=[mean(red_x),mean(red_y)];
        xred=red_C(1,2);
        yred=red_C(1,1);
    else
        xred=0;
        yred=0;
    end  
    clearvars -except yred xred;
end