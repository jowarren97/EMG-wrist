clc
clear all
delete(instrfindall)
%%
% Save the serial port name in comPort variable.

comPort = 'COM11';
%% 
% It creates a serial element calling the function "setupSerial"

if(~exist('serialFlag','var'))
    [arduino,serialFlag] = setupSerial(comPort);
end

%% GENERATE SINE WAVE OUTPUT
% 
% t = 0:pi/100:2*pi;
% y = 200*sin(t);
% 
% y2 = zeros(1,numel(y));
% 
% for i = 2:numel(y)
%     y2(i) = y(i)-y(i-1); %difference betw consecutive values
% end
% 
% y2(1) = y(1)-y(numel(y)-1);
% 
% y2 = round(y2); %'round' better than 'floor'
% %as floor resulted in under-rotation

%% 
pos = [2000 4000 6000 2000 1000];
% for i = 1:numel(y2)
%     fprintf(arduino,'%f', y2(i));
%     pause(0.005);
% end
%val = fscanf(arduino, '%f');


% for i = 1:numel(pos)
%     fprintf(arduino, '%f', pos(i));
%     pause(1);
% end

%%
%fclose(serial(comPort))
