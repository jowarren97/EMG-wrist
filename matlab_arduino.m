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

%% 
steps = 2000;

fprintf(arduino,'%f', steps);

% for i = 1:4
%     fprintf(arduino,'R');
%     pause(0.1);
%     fprintf(arduino,'%d', steps);
%     pause(0.9);
% end

% for i = 1:10
%     fprintf(arduino,'%f', steps);
%     pause(1);
% end

%%
% 
% mode = 'R';
% 
% while (get(button,'Value') == 0 )
%     
%     tc = readTemp(arduino,mode);
%     
%     tcdata = [tcdata(2:end),tc];
%     
%     set(l,'Ydata',tcdata);
%     
%     drawnow;
%     
%     pause(1);
% end

% To remeber: when you are satisfied with you measurement click on the 
% "stop" button in the bottom left corner of the figure. Now you have to
% close the serial object "Arduino" using the command "fclose(arduino)",
% and close the h figure typing "close(h)". Now in "tcdata" variable you
% have your real time data. 
