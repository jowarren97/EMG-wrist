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

%% GENERATE OUTPUT
% sine wave
t = 0:pi/100:10*pi;
pos = 180*sin(t);
pos = round(pos); %'round' better than 'floor'
%as floor resulted in under-rotation

% %step
% pos = zeros(1, 100);
% pos(50:100) = 100;

%% SEND OUTPUT

data = zeros(1,numel(pos));

elapsedtime = 0;

for i = 1:numel(pos)
    tic;
    position = strcat(num2str(pos(i)),',0');
    fprintf(arduino, position);
    elapsedtime = elapsedtime + toc;
    postime(i) = elapsedtime;
   
    pause(0.05);
    
    tic;
    data(i) = readTemp(arduino, 'R');
    elapsedtime = elapsedtime + toc;
    datatime(i) = elapsedtime;

end

%%
data = data-data(1);
figure();
plot(datatime, data);
title('Sine Function, 500 steps/s')
xlabel('time/s')
ylabel('Angular position/ deg')
hold on;
plot(postime, pos);
fclose(serial(comPort))
