function writeOutDataV2(obj,event,hObject,handles)
global DataArr

%txmsg='getData'; %Currently, if OMAP receives anything, it transmits the same set of floats
%fprintf('Querying DSP for data...\n');
txmsg=uint8([253 handles.TCPIP.txmsg 255]); %string 'GetData' is arbitrary for now.
%Conceivably, we can set up DSP to send back different things based on transmitted strings
handles.TCPIP.out_stream.write(txmsg);



tic
while(toc<0.5 && handles.TCPIP.in_stream.available<1)
    %wait for either 0.5 seconds to pass or the input stream to show
    %available bytes
    %fprintf('waiting for more bytes on stream \n')
end
% toc

if(handles.TCPIP.in_stream.available()<1)
    fprintf('No bytes to read in input stream. Stopping timer object \n');
    
    %stop the timer just like i do in disconnect button callback 
    %(calling disconnect callback from here wont let me pass the handles structure.
    %From this function's perspective, the 'disconnect' callback function 
    %takes only two arguments, not third argument for 'handles'.)
    stop(handles.TCPIP.writeOutTimer)
    fprintf('Timer Object Stopped\n')
    handles.TCPIP.in_stream.close();
    handles.TCPIP.out_stream.close();
    handles.TCPIP.mySocket.close();
    handles.TCPIP.mySocket = [];
    set(handles.tb_TickerTxt,'String','Conn Closed')
    set(handles.tb_TickerTxt,'BackgroundColor',[0.941 0.941 0.941])
    fprintf('Connection successfully closed\n')
    fprintf('Socket closed\nRESTART VBDSPCOMM.\n')
else
    handles.TCPIP.in_stream.read(); %get rid of start character
    numchars_str=[];
    
    tempstr=[];
    numchars_str=[];
    while (isempty(tempstr)||char(tempstr)~=',') %order of this while condition is important, because " []~=',' " evaluates to "[]"
        numchars_str=[numchars_str,tempstr];
        tempstr=handles.TCPIP.in_stream.read();
    end
    %fprintf('First comma has been read into the buffer... \n');
    numchars=str2num(char(numchars_str)); % gets number of remaining characters in message
    %fprintf('number of data characters:  %d \n',numchars);
    rxBytes=handles.TCPIP.reader.read(handles.TCPIP.mySocket,numchars);
    
    tempstr=handles.TCPIP.in_stream.read(); %read off the end character
    %fprintf('Read off end char: %d\n',tempstr);
    
    out1=handles.TCPIP.reader.bfr;
    
    scanString=[];
    for i=1:handles.TCPIP.numFloats-1
        scanString=[scanString '%f,'];
    end
    scanString=[scanString,'%f'];
    
    [DataArr]=sscanf(char(out1(1:numchars)),scanString);
    %set(handles.TCPIP.DataArr,DataArr)
    %set(handles.TCPIP.okToWrite,0)
    %set(handles.TCPIP.okToRead,1)
    
    set(handles.myPlot,'Marker','o','MarkerSize',30);
    set(handles.myPlot,'XData',DataArr(5));
    set(handles.myPlot,'YData',DataArr(6));
    set(handles.myPlot,'ZData',DataArr(8));
    set(handles.axes1,'Xlim',[-10,10]);
    set(handles.axes1,'Ylim',[-10,10]);
    set(handles.axes1,'Zlim',[-10,10]);
end
%guidata(hObject,handles)


