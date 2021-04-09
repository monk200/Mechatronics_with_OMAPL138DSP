function varargout = TCPIP_V6_2_wImgTx(varargin)
% TCPIP_V6_2_wImgTx MATLAB code for TCPIP_V6_2_wImgTx.fig
%      TCPIP_V6_2_wImgTx, by itself, creates a new TCPIP_V6_2_wImgTx or raises the existing
%      singleton*.
%
%      H = TCPIP_V6_2_wImgTx returns the handle to a new TCPIP_V6_2_wImgTx or the handle to
%      the existing singleton*.
%
%      TCPIP_V6_2_wImgTx('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in TCPIP_V6_2_wImgTx.M with the given input arguments.
%
%      TCPIP_V6_2_wImgTx('Property','Value',...) creates a new TCPIP_V6_2_wImgTx or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before TCPIP_V6_2_wImgTx_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to TCPIP_V6_2_wImgTx_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help TCPIP_V6_2_wImgTx

% Last Modified by GUIDE v2.5 31-Mar-2014 11:23:03

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @TCPIP_V6_2_wImgTx_OpeningFcn, ...
                   'gui_OutputFcn',  @TCPIP_V6_2_wImgTx_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT

%notes 3/12/14
%This version, I am just making DataArr a global
%variable. Not sure how this will effect speed yet, but it makes
%communicating these values between functions much simpler.

%I am able to modify any variables in the original gui using the timer
%function provided I am careful about a few things:
%   1) I specify input arguments in the following way:
%     "set(handles.TCPIP.writeOutTimer,'TimerFcn',{'writeOutData',hObject,handles},...)"
%     Note that the value of hObject and handles when this set statement is
%     called is the value which is seen in the timer function every time it
%     runs. If this set statement is made and then a new item is added to
%     the handles structure, this item will not be visible in the timer
%     function.
%   2)  I do any gui updating (the plot and any text) within the timer function.
%      This ensures that the data I am using has just been read from the TCPIP
%      server, and that the timer function isn't trying to write to the
%      variables as I am reading from them. If the plotting etc. takes too
%      long, i.e. long enough for the next call of the timer function to   
%      occur, the timer function is setup so that it will "drop" the next 
%      timer function call. This setting is also helpful when debugging so
%      that any additional timer function calls are dropped while
%      debugging, rather than being run in the background.

% --- Executes just before TCPIP_V6_2_wImgTx is made visible.
function TCPIP_V6_2_wImgTx_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to TCPIP_V6_2_wImgTx (see VARARGIN)

global DataArr;
DataArr=[];

handles.TCPIP.imgRows=144;
handles.TCPIP.imgCols=176;
C=zeros(handles.TCPIP.imgRows,handles.TCPIP.imgCols,3); %blank colorData

handles.TCPIP.numFloats=10; %change if you want to send more floats
handles.TCPIP.mySocket = [];
handles.TCPIP.out_stream = [];
handles.TCPIP.in_stream = [];
handles.TCPIP.txmsg = 'GetData';
handles.UserData=[];
handles.myPlot=plot(handles.axes1,[-1]); %we initialize the plot to have some data so it is given a handle in our handles structure
handles.myImagePlot=image(C,'parent',handles.axes1);
% set(handles.axes1,'YDir','reverse');


set(handles.figure1,'toolbar','figure'); %this just gives us all the nice figure tools we see in every matlab figure


%We don't give the timer a function yet. This is because our handles
%structure doesn't yet contain in_stream and out_stream objects. If we
%made the handles structure an input argument to the timer function now, it
%would pass that version of the handles structure (by value) to the timer function
%whenever 'timerfunc' is called. That version of the handles structure
%doesn't contain any tcpip objects, so we wouldn't be able to use them.

handles.TCPIP.writeOutTimer=timer('ErrorFcn','disp(''Timer object error'')','ExecutionMode','fixedRate');

% Choose default command line output for TCPIP_V6_2_wImgTx
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes TCPIP_V6_2_wImgTx wait for user response (see UIRESUME)
% uiwait(handles.figure1);

% --- Outputs from this function are returned to the command line.
function varargout = TCPIP_V6_2_wImgTx_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;

function edt_RobotIP_Callback(hObject, eventdata, handles)
% hObject    handle to edt_RobotIP (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edt_RobotIP as text
%        str2double(get(hObject,'String')) returns contents of edt_RobotIP as a double


% --- Executes during object creation, after setting all properties.
function edt_RobotIP_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edt_RobotIP (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function edt_Port_Callback(hObject, eventdata, handles)
% hObject    handle to edt_Port (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edt_Port as text
%        str2double(get(hObject,'String')) returns contents of edt_Port as a double

% --- Executes during object creation, after setting all properties.
function edt_Port_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edt_Port (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on button press in pb_Connect.
function pb_Connect_Callback(hObject, eventdata, handles)
% hObject    handle to pb_Connect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%set ticker text to blue while it tries to connect
set(handles.tb_TickerTxt,'String','Connecting...')
set(handles.tb_TickerTxt,'BackgroundColor',[0.3 0.3 1])

%check to see if Socket object already exists. If it does, then we do
%nothing.
if(~isempty(handles.TCPIP.mySocket))
    fprintf('Socket already exists.\n')
    set(handles.tb_TickerTxt,'String','Connected')
    set(handles.tb_TickerTxt,'BackgroundColor',[0.3 1 0.3])
else
    %No socket has been opened yet
    port=str2num(get(handles.edt_Port,'String'));
    host=get(handles.edt_RobotIP,'String');
    import java.net.Socket
    import java.io.*
    javaaddpath('.') % we add the current directory to our java path so we can make an instance of our custom class
    
    try
        handles.TCPIP.reader=InputStreamByteWrapper;
        wrapperCreated=true;
    catch
        %fprintf('Socket was opened, but Java Wrapper class not recognized.\n');
        %fprintf('Socket will be closed...\n\n');
        %PBcloseSocket_Callback(hObject, eventdata, handles)
        fprintf('Error:Does your current directory contain InputStreamByteWrapper.class file?.\n');
        set(handles.tb_TickerTxt,'String','Error')
        set(handles.tb_TickerTxt,'BackgroundColor',[1 0.3 0.3])
        wrapperCreated=false;
    end
    
    %if we successfully made wrapper class, we try to open a socket
    if(wrapperCreated)
        try
            handles.TCPIP.mySocket = Socket(host, port);
            handles.TCPIP.in_stream  = handles.TCPIP.mySocket.getInputStream;
            handles.TCPIP.out_stream = handles.TCPIP.mySocket.getOutputStream;
            fprintf('New socket opened.\nHost: %s, Port: %d \n',host,port);
            %Initialize timers here because all the subfields which we will
            %refer to in the timer function now exist
            set(handles.TCPIP.writeOutTimer,'TimerFcn',{'writeOutData',hObject,handles},'Period',0.003) %for now i set period to be reasonably long
            fprintf('Timer reinitialized\n');
            start(handles.TCPIP.writeOutTimer);
            fprintf('Timer started\n');
            set(handles.tb_TickerTxt,'String','Connected');
            set(handles.tb_TickerTxt,'BackgroundColor',[0.3 1 0.3])
        catch
            clear reader; % this gets rid of the java object referred to by reader
            handles.TCPIP.mySocket=[]; %not sure if this line is necessary. We just don't want 'clear java' command to leave TCPIP.mySocket undefined. 
            %Currently I use handles.TCPIP.mySocket=[] to mean that we will
            %need to create a new socket object when the user wishes to
            %connect, and not reuse an old socket. In this way, the
            %behavior of the connect button is the same regardless of if
            %the user just opened the application or has just closed his
            %last socket.
            fprintf('Error: Socket not opened successfully.\n')
            fprintf('Check host ip, and socket number.\n')
            fprintf('Also, make sure robot is running VBDSPComm.\n')
            set(handles.tb_TickerTxt,'String','Error')
            set(handles.tb_TickerTxt,'BackgroundColor',[1 0.3 0.3])
        end
    end
     
    guidata(hObject,handles);
end

% --- Executes on button press in pb_Disconnect.
function pb_Disconnect_Callback(hObject, eventdata, handles)
% hObject    handle to pb_Disconnect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
if(~isempty(handles.TCPIP.mySocket))
    stop(handles.TCPIP.writeOutTimer)
    fprintf('Timer Object Stopped\n')
    handles.TCPIP.in_stream.close();
    handles.TCPIP.out_stream.close();
    handles.TCPIP.mySocket.close();
    handles.TCPIP.mySocket = [];
    set(handles.tb_TickerTxt,'String','Conn Closed')
    set(handles.tb_TickerTxt,'BackgroundColor',[0.941 0.941 0.941])
    fprintf('Connection successfully closed\n')
    fprintf('Socket closed\nRestart VBimgTX before connecting again.\n')
    guidata(hObject,handles)
else
    set(handles.tb_TickerTxt,'String','Error')
    set(handles.tb_TickerTxt,'BackgroundColor',[1 0.3 0.3])
    fprintf('Socket was already closed \n')
end

% --- Executes on button press in tb_TickerTxt.
function tb_TickerTxt_Callback(hObject, eventdata, handles)
% hObject    handle to tb_TickerTxt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%just using this assignment to place breakpoints next to...
i=1;


% --- Executes on button press in pb_X.
function pb_X_Callback(hObject, eventdata, handles)
% hObject    handle to pb_X (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% --- Executes on button press in pb_Y.
function pb_Y_Callback(hObject, eventdata, handles)
% hObject    handle to pb_Y (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% --- Executes on button press in pb_Theta.
function pb_Theta_Callback(hObject, eventdata, handles)
% hObject    handle to pb_Theta (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% --- Executes when user attempts to close figure1.
function figure1_CloseRequestFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
pb_Disconnect_Callback(hObject, eventdata, handles)
try
    %stop(handles.TCPIP.readInTimer)
    stop(handles.TCPIP.writeOutTimer)
    %delete(handles.TCPIP.readInTimer)
    delete(handles.TCPIP.writeOutTimer)
    fprintf('Timer objects successfully deleted\n')
catch
    fprintf('something wrong with deletion of timers\n')
end
% Hint: delete(hObject) closes the figure
delete(hObject);
