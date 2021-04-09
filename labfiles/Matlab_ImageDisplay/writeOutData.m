function writeOutData(obj,event,hObject,handles)
%global PictureData
persistent commandState
persistent C
persistent readBytes

if(isempty(commandState))
    commandState=0;
end

nCols=handles.TCPIP.imgCols;
nRows=handles.TCPIP.imgRows;
out1=zeros(nRows*nCols*3,1);
if(isempty(C))
    C=zeros(nRows,nCols,3);
end

byteChunk=1000; %the maximum amount of bytes we read at a single time from socket
rxTot=0;
switch commandState
    case 0
        txmsg=uint8('I1');
        handles.TCPIP.out_stream.write(txmsg);
        commandState=1;
    case 1
        readBytes=0; %read bytes holds the number of bytes already read from the socket
        while(readBytes<10000);
            if (handles.TCPIP.in_stream.available()>0);
                %the available() method only returns approximately how many
                %characters are in the stream. Trying to read more than
                %5000 gives an error, so we instead read blocks of 2000 for
                %now
                
                rxBytes=handles.TCPIP.reader.read(handles.TCPIP.mySocket,min(10000-rxTot,byteChunk));
                rxTot=rxTot+rxBytes; %rxTot keeps track of how many we have read in this case statement
                readBytes=readBytes+rxBytes;
                out1(readBytes-rxBytes+1:readBytes)=typecast(int8(handles.TCPIP.reader.bfr(1:rxBytes)),'uint8');
            end
        end
        for i=((readBytes-10000)+1:readBytes)
            %we need to figure out what row and column we are referring to
            %with index i and put data in persistent C variable
            %note, we may be able to use a property of the color plot to
            %not use persistent variables
            
            row=floor((i-1)/(nCols*3))+1;
            col=floor(mod((i-1),nCols*3)/3)+1;
            bgr=mod(mod((i-1),nCols*3),3)+1; %bgr goes from 1,2,3 (1=b,2=g,3=r)
            %convert bgr to rgb for matlab
            switch bgr
                case 1
                    rgb=3;
                case 2
                    rgb=2;
                otherwise
                    rgb=1;
            end
            
            C(row,col,rgb)=out1(i);
        end
        
        commandState=2;
    case 2
        txmsg=uint8('I2');
        handles.TCPIP.out_stream.write(txmsg);
        commandState=3;
    case 3
        
        while(readBytes<20000);
            if (handles.TCPIP.in_stream.available()>0);
                rxBytes=handles.TCPIP.reader.read(handles.TCPIP.mySocket,min(10000-rxTot,byteChunk));
                rxTot=rxTot+rxBytes; %rxTot keeps track of how many we have read in this case statement
                readBytes=readBytes+rxBytes;
                out1(readBytes-rxBytes+1:readBytes)=typecast(int8(handles.TCPIP.reader.bfr(1:rxBytes)),'uint8');
            end
        end
        for i=((readBytes-10000)+1:readBytes)
            
            row=floor((i-1)/(nCols*3))+1;
            col=floor(mod((i-1),nCols*3)/3)+1;
            bgr=mod(mod((i-1),nCols*3),3)+1; %bgr goes from 1,2,3 (1=b,2=g,3=r)
            %convert bgr to rgb for matlab
            switch bgr
                case 1
                    rgb=3;
                case 2
                    rgb=2;
                otherwise
                    rgb=1;
            end
            
            C(row,col,rgb)=out1(i);
        end
        
        commandState=4;
    case 4
        txmsg=uint8('I3');
        handles.TCPIP.out_stream.write(txmsg);
        commandState=5;
    case 5
        
        while(readBytes<30000);
            if (handles.TCPIP.in_stream.available()>0);
                rxBytes=handles.TCPIP.reader.read(handles.TCPIP.mySocket,min(10000-rxTot,byteChunk));
                rxTot=rxTot+rxBytes; %rxTot keeps track of how many we have read in this case statement
                readBytes=readBytes+rxBytes;
                out1(readBytes-rxBytes+1:readBytes)=typecast(int8(handles.TCPIP.reader.bfr(1:rxBytes)),'uint8');
            end
        end
        for i=((readBytes-10000)+1:readBytes)
            
            row=floor((i-1)/(nCols*3))+1;
            col=floor(mod((i-1),nCols*3)/3)+1;
            bgr=mod(mod((i-1),nCols*3),3)+1; %bgr goes from 1,2,3 (1=b,2=g,3=r)
            %convert bgr to rgb for matlab
            switch bgr
                case 1
                    rgb=3;
                case 2
                    rgb=2;
                otherwise
                    rgb=1;
            end
            
            C(row,col,rgb)=out1(i);
        end
        
        commandState=6;
    case 6
        txmsg=uint8('I4');
        handles.TCPIP.out_stream.write(txmsg);
        commandState=7;
    case 7
        
        while(readBytes<40000);
            if (handles.TCPIP.in_stream.available()>0);
                rxBytes=handles.TCPIP.reader.read(handles.TCPIP.mySocket,min(10000-rxTot,byteChunk));
                rxTot=rxTot+rxBytes; %rxTot keeps track of how many we have read in this case statement
                readBytes=readBytes+rxBytes;
                out1(readBytes-rxBytes+1:readBytes)=typecast(int8(handles.TCPIP.reader.bfr(1:rxBytes)),'uint8');
            end
        end
        for i=((readBytes-10000)+1:readBytes)
            
            row=floor((i-1)/(nCols*3))+1;
            col=floor(mod((i-1),nCols*3)/3)+1;
            bgr=mod(mod((i-1),nCols*3),3)+1; %bgr goes from 1,2,3 (1=b,2=g,3=r)
            %convert bgr to rgb for matlab
            switch bgr
                case 1
                    rgb=3;
                case 2
                    rgb=2;
                otherwise
                    rgb=1;
            end
            
            C(row,col,rgb)=out1(i);
        end
        
        commandState=8;
    case 8
        txmsg=uint8('I5');
        handles.TCPIP.out_stream.write(txmsg);
        commandState=9;
    case 9
        
        while(readBytes<50000);
            if (handles.TCPIP.in_stream.available()>0)
                rxBytes=handles.TCPIP.reader.read(handles.TCPIP.mySocket,min(10000-rxTot,byteChunk));
                rxTot=rxTot+rxBytes; %rxTot keeps track of how many we have read in this case statement
                readBytes=readBytes+rxBytes;
                out1(readBytes-rxBytes+1:readBytes)=typecast(int8(handles.TCPIP.reader.bfr(1:rxBytes)),'uint8');
            end
        end
        for i=((readBytes-10000)+1:readBytes)
            
            row=floor((i-1)/(nCols*3))+1;
            col=floor(mod((i-1),nCols*3)/3)+1;
            bgr=mod(mod((i-1),nCols*3),3)+1; %bgr goes from 1,2,3 (1=b,2=g,3=r)
            %convert bgr to rgb for matlab
            switch bgr
                case 1
                    rgb=3;
                case 2
                    rgb=2;
                otherwise
                    rgb=1;
            end
            
            C(row,col,rgb)=out1(i);
        end
        
        commandState=10;
    case 10
        txmsg=uint8('I6');
        handles.TCPIP.out_stream.write(txmsg);
        commandState=11;
    case 11
        
        while(readBytes<60000);
            if (handles.TCPIP.in_stream.available()>0);
                rxBytes=handles.TCPIP.reader.read(handles.TCPIP.mySocket,min(10000-rxTot,byteChunk));
                rxTot=rxTot+rxBytes; %rxTot keeps track of how many we have read in this case statement
                readBytes=readBytes+rxBytes;
                out1(readBytes-rxBytes+1:readBytes)=typecast(int8(handles.TCPIP.reader.bfr(1:rxBytes)),'uint8');
            end
        end
        for i=((readBytes-10000)+1:readBytes)
            row=floor((i-1)/(nCols*3))+1;
            col=floor(mod((i-1),nCols*3)/3)+1;
            bgr=mod(mod((i-1),nCols*3),3)+1; %bgr goes from 1,2,3 (1=b,2=g,3=r)
            %convert bgr to rgb for matlab
            switch bgr
                case 1
                    rgb=3;
                case 2
                    rgb=2;
                otherwise
                    rgb=1;
            end
            
            C(row,col,rgb)=out1(i);
        end
        
        commandState=12;
    case 12
        txmsg=uint8('I7');
        handles.TCPIP.out_stream.write(txmsg);
        commandState=13;
    case 13
        
        while(readBytes<70000);
            if (handles.TCPIP.in_stream.available()>0);
                rxBytes=handles.TCPIP.reader.read(handles.TCPIP.mySocket,min(10000-rxTot,byteChunk));
                rxTot=rxTot+rxBytes; %rxTot keeps track of how many we have read in this case statement
                readBytes=readBytes+rxBytes;
                out1(readBytes-rxBytes+1:readBytes)=typecast(int8(handles.TCPIP.reader.bfr(1:rxBytes)),'uint8');
            end
        end
        for i=((readBytes-10000)+1:readBytes)
            
            row=floor((i-1)/(nCols*3))+1;
            col=floor(mod((i-1),nCols*3)/3)+1;
            bgr=mod(mod((i-1),nCols*3),3)+1; %bgr goes from 1,2,3 (1=b,2=g,3=r)
            %convert bgr to rgb for matlab
            switch bgr
                case 1
                    rgb=3;
                case 2
                    rgb=2;
                otherwise
                    rgb=1;
            end
            
            C(row,col,rgb)=out1(i);
        end
        
        commandState=14;
    case 14
        txmsg=uint8('I8');
        handles.TCPIP.out_stream.write(txmsg);
        commandState=15;
    case 15
        
        while(readBytes<76032);
            if (handles.TCPIP.in_stream.available()>0);
                rxBytes=handles.TCPIP.reader.read(handles.TCPIP.mySocket,min(6032-rxTot,754));
                rxTot=rxTot+rxBytes; %rxTot keeps track of how many we have read in this case statement
                readBytes=readBytes+rxBytes;
                out1(readBytes-rxBytes+1:readBytes)=typecast(int8(handles.TCPIP.reader.bfr(1:rxBytes)),'uint8');
            end
        end
        for i=((readBytes-6032)+1:readBytes)
            
            row=floor((i-1)/(nCols*3))+1;
            col=floor(mod((i-1),nCols*3)/3)+1;
            bgr=mod(mod((i-1),nCols*3),3)+1; %bgr goes from 1,2,3 (1=b,2=g,3=r)
            %convert bgr to rgb for matlab
            switch bgr
                case 1
                    rgb=3;
                case 2
                    rgb=2;
                otherwise
                    rgb=1;
            end
            
            C(row,col,rgb)=out1(i);
        end
        C=C/256; %normalize c array from 0 to 1
        commandState=0;
        
        %%%%%%%%%%%%%%plot color data on MATLAB GUI%%%%%%%%%%%%%%
        %Add lines below to change how image is plotted
        %
        %Change Plot properties by using "set" and "get" methods on the plot object
        %
        %   Syntax: "set(handles.myImagePlot,[property],[value]);"
        %   where [property] and [value] are a valid pair
        %
        %   to view available properties of any object use the "get"
        %   method without any arguments, as in: "get(handles.myImagePlot)";
        %  
        %   for more information on get/set methods, see the documentation
        %   at: http://www.mathworks.com/help/matlab/ref/get.html
        %
        set(handles.myImagePlot,'CData',C);
        set(handles.axes1,'YDir','normal');
        set(handles.axes1,'XDir','reverse'); %Picture backwards in default setting
        
        
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    otherwise
end

%guidata(hObject,handles)


