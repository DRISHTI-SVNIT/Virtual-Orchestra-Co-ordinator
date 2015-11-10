cd('C:/Users/Admin/Documents/GitHub/Virtual-Orchestra-Co-ordinator/MATLAB code/');
warning off;
cam = webcam('Integrated Webcam');
cam.Resolution='160x120';

global paint tempimg;
%s=serial('COM7','BaudRate',38400);
%set(s,'Terminator','0');
%fopen(s);
InitialiseGUI;

prompt='New or Old? Press 1 for New and 2 for Old .';
useranswer=input(prompt);
if useranswer==1
UI(cam);
end
clearvars -except value binary flagxx brightfactor gamma1 cam s tempimg paint

fig = figure;

SE=strel('disk',1);
flag=0;
flag_prog=0;

paint=zeros(120,160);
data=zeros(2,2);
dilatepaint=paint;
tempdilatepaint=struct('cdata',zeros(120,160));

[startcoordinate]=RunwithGUIPaint2(cam);
data(1,:)=[floor(startcoordinate(2)),floor(startcoordinate(1))];

if(data(1,1)<1) 
        data(1,1)=1;
end
if(data(1,2)<1) 
    data(1,2)=1;
end

for j=2:20
        tempdilatepaint(j-1).cdata=zeros(120,160);
        
        [coordinate]=RunwithGUIPaint2(cam);
        data(j,:)=[floor(coordinate(2)),floor(coordinate(1))];
        if(data(j,1)<1) 
            data(j,1)=1;
        end
        if(data(j,2)<1) 
            data(j,2)=1;
        end
        
        x=linspace(data(j-1,1),data(j,1),20);
        y=linspace(data(j-1,2),data(j,2),20);
        index=sub2ind([120 160],round(x),round(y));
        
        tempdilatepaint(j-1).cdata(index)=1;
        clear index;
        tempdilatepaint(j-1).cdata=imdilate(tempdilatepaint(j-1).cdata,SE);
        dilatepaint=dilatepaint|tempdilatepaint(j-1).cdata;
        figure(fig); fig.OuterPosition = [1,1,1366,720]; hold on;
        imshowpair(dilatepaint,tempimg,'montage');
end        
data(1,:)=data(19,:);
data(2,:)=data(20,:);
while flag_prog==0
        data(1,:)=data(2,:);
        dilatepaint=zeros(120,160);
        for j=1:18
        tempdilatepaint(j).cdata=zeros(120,160);
        tempdilatepaint(j).cdata=tempdilatepaint(j).cdata|tempdilatepaint(j+1).cdata;
        dilatepaint=dilatepaint|tempdilatepaint(j).cdata;
        end
        tempdilatepaint(19).cdata=zeros(120,160);
        [coordinate]=RunwithGUIPaint2(cam);
        data(2,:)=[floor(coordinate(2)),floor(coordinate(1))];
        if(data(2,1)<1) 
            data(2,1)=1;
        end
        if(data(2,2)<1) 
            data(2,2)=1;
        end
        
        x=linspace(data(1,1),data(2,1),20);
        y=linspace(data(1,2),data(2,2),20);
        index=sub2ind([120 160],round(x),round(y));
        
        tempdilatepaint(19).cdata(index)=1;
        clear index;
        tempdilatepaint(19).cdata=imdilate(tempdilatepaint(19).cdata,SE);
        dilatepaint=dilatepaint|tempdilatepaint(19).cdata;
        
        figure(fig); fig.OuterPosition = [1,1,1366,720]; hold on;
        imshowpair(dilatepaint,tempimg,'montage');
        if flag==1
            data_x=round(coordinate(3)*20);
            if data_x<0
                data_x=-1*data_x;
            end
            if data_x>175
                data_x=175;
            end
            sendx=char(data_x);
            %if fgets(s)=='0'
            %fwrite(s,sendx);
            data_x
            %end
        end
    
    ocrresult=ocr(dilatepaint,'TextLayout','Block','CharacterSet','C.N');
    if ocrresult.WordConfidences>0.6
        if ocrresult.Words{1} == 'C'
            flag=1;
            %fwrite(s,201);
            fprintf('z');
        elseif ocrresult.Words{1} == '.'
            flag=0;
            %fwrite(s,200);
            fprintf('c');
        elseif ocrresult.Words{1} == 'N'
            flag_prog=1;
            fprintf('n');
        end
    end
end
%fclose(s);
%delete(s);
close all;
clearvars -except value brightfactor gamma1 upperx lowerx s;