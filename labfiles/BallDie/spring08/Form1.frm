VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "5"
   ClientHeight    =   8052
   ClientLeft      =   48
   ClientTop       =   336
   ClientWidth     =   11484
   LinkTopic       =   "Form1"
   ScaleHeight     =   8052
   ScaleWidth      =   11484
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton drawCanButton 
      Caption         =   "POSITION CAN"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   732
      Left            =   7680
      TabIndex        =   1
      Top             =   5400
      Width           =   1692
   End
   Begin VB.CommandButton drawButoon 
      Caption         =   "DRAW BALLS"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   852
      Left            =   2040
      TabIndex        =   0
      Top             =   6840
      Width           =   1692
   End
   Begin VB.Shape Shape3 
      FillColor       =   &H00FFFFFF&
      FillStyle       =   6  'Cross
      Height          =   1092
      Left            =   1320
      Shape           =   3  'Circle
      Top             =   5400
      Width           =   1092
   End
   Begin VB.Label Label2 
      Alignment       =   2  'Center
      BackColor       =   &H8000000E&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "RANDOM BALL POSITIONER"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.8
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FF8080&
      Height          =   372
      Left            =   600
      TabIndex        =   3
      Top             =   240
      Width           =   4092
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      BackColor       =   &H8000000E&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "RANDOM CAN POSITIONER"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.8
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FF8080&
      Height          =   372
      Left            =   6480
      TabIndex        =   2
      Top             =   480
      Width           =   4092
   End
   Begin VB.Shape can 
      BackColor       =   &H000000FF&
      BackStyle       =   1  'Opaque
      BorderColor     =   &H00000000&
      FillColor       =   &H000000FF&
      Height          =   264
      Index           =   5
      Left            =   7440
      Shape           =   3  'Circle
      Top             =   3720
      Width           =   264
   End
   Begin VB.Shape can 
      BackColor       =   &H000000FF&
      BackStyle       =   1  'Opaque
      BorderColor     =   &H00000000&
      FillColor       =   &H000000FF&
      Height          =   264
      Index           =   4
      Left            =   7200
      Shape           =   3  'Circle
      Top             =   2280
      Width           =   264
   End
   Begin VB.Shape can 
      BackColor       =   &H000000FF&
      BackStyle       =   1  'Opaque
      BorderColor     =   &H00000000&
      FillColor       =   &H000000FF&
      Height          =   264
      Index           =   3
      Left            =   9600
      Shape           =   3  'Circle
      Top             =   2040
      Width           =   264
   End
   Begin VB.Shape can 
      BackColor       =   &H000000FF&
      BackStyle       =   1  'Opaque
      BorderColor     =   &H00000000&
      FillColor       =   &H000000FF&
      Height          =   264
      Index           =   2
      Left            =   7680
      Shape           =   3  'Circle
      Top             =   1440
      Width           =   264
   End
   Begin VB.Shape can 
      BackColor       =   &H000000FF&
      BackStyle       =   1  'Opaque
      BorderColor     =   &H00000000&
      FillColor       =   &H000000FF&
      Height          =   264
      Index           =   1
      Left            =   9720
      Shape           =   3  'Circle
      Top             =   2880
      Width           =   264
   End
   Begin VB.Line Line11 
      BorderColor     =   &H00FF0000&
      BorderWidth     =   5
      Index           =   1
      X1              =   8520
      X2              =   8520
      Y1              =   2880
      Y2              =   3120
   End
   Begin VB.Line Line12 
      BorderColor     =   &H00FF0000&
      BorderWidth     =   5
      Index           =   1
      X1              =   8400
      X2              =   8640
      Y1              =   3000
      Y2              =   3000
   End
   Begin VB.Line Line12 
      BorderColor     =   &H00FF0000&
      BorderWidth     =   5
      Index           =   0
      X1              =   2640
      X2              =   2880
      Y1              =   5160
      Y2              =   5160
   End
   Begin VB.Line Line11 
      BorderColor     =   &H00FF0000&
      BorderWidth     =   5
      Index           =   0
      X1              =   2760
      X2              =   2760
      Y1              =   5040
      Y2              =   5280
   End
   Begin VB.Shape can 
      BackColor       =   &H000000FF&
      BackStyle       =   1  'Opaque
      BorderColor     =   &H00000000&
      FillColor       =   &H000000FF&
      Height          =   264
      Index           =   0
      Left            =   8400
      Shape           =   3  'Circle
      Top             =   1080
      Width           =   264
   End
   Begin VB.Shape internalBallArea 
      BorderColor     =   &H80000007&
      FillColor       =   &H00FFFFFF&
      FillStyle       =   0  'Solid
      Height          =   2000
      Left            =   7500
      Shape           =   3  'Circle
      Top             =   2000
      Width           =   2000
   End
   Begin VB.Shape Shape2 
      Height          =   3996
      Left            =   6480
      Shape           =   3  'Circle
      Top             =   960
      Width           =   3996
   End
   Begin VB.Shape Shape1 
      FillColor       =   &H00FFFFFF&
      FillStyle       =   6  'Cross
      Height          =   1092
      Left            =   2880
      Shape           =   3  'Circle
      Top             =   5400
      Width           =   1092
   End
   Begin VB.Shape golfBall 
      BackColor       =   &H000080FF&
      BackStyle       =   1  'Opaque
      Height          =   252
      Index           =   7
      Left            =   4200
      Shape           =   3  'Circle
      Top             =   4440
      Width           =   252
   End
   Begin VB.Shape golfBall 
      BackColor       =   &H000080FF&
      BackStyle       =   1  'Opaque
      Height          =   252
      Index           =   6
      Left            =   3720
      Shape           =   3  'Circle
      Top             =   3120
      Width           =   252
   End
   Begin VB.Shape golfBall 
      BackColor       =   &H000080FF&
      BackStyle       =   1  'Opaque
      Height          =   252
      Index           =   5
      Left            =   2640
      Shape           =   3  'Circle
      Top             =   960
      Width           =   252
   End
   Begin VB.Shape golfBall 
      BackColor       =   &H000080FF&
      BackStyle       =   1  'Opaque
      Height          =   252
      Index           =   4
      Left            =   3720
      Shape           =   3  'Circle
      Top             =   2040
      Width           =   252
   End
   Begin VB.Shape golfBall 
      BackColor       =   &H000080FF&
      BackStyle       =   1  'Opaque
      Height          =   252
      Index           =   3
      Left            =   1440
      Shape           =   3  'Circle
      Top             =   2040
      Width           =   252
   End
   Begin VB.Line Line10 
      X1              =   1800
      X2              =   3600
      Y1              =   3600
      Y2              =   3600
   End
   Begin VB.Line Line9 
      X1              =   3600
      X2              =   3600
      Y1              =   1800
      Y2              =   3600
   End
   Begin VB.Line Line8 
      X1              =   1800
      X2              =   1800
      Y1              =   1800
      Y2              =   3600
   End
   Begin VB.Shape golfBall 
      BackColor       =   &H000080FF&
      BackStyle       =   1  'Opaque
      Height          =   252
      Index           =   2
      Left            =   1440
      Shape           =   3  'Circle
      Top             =   3120
      Width           =   252
   End
   Begin VB.Shape golfBall 
      BackColor       =   &H000080FF&
      BackStyle       =   1  'Opaque
      Height          =   252
      Index           =   1
      Left            =   1800
      Shape           =   3  'Circle
      Top             =   4440
      Width           =   252
   End
   Begin VB.Shape golfBall 
      BackColor       =   &H000080FF&
      BackStyle       =   1  'Opaque
      Height          =   252
      Index           =   0
      Left            =   960
      Shape           =   3  'Circle
      Top             =   4440
      Width           =   252
   End
   Begin VB.Line Line7 
      X1              =   3360
      X2              =   4560
      Y1              =   4920
      Y2              =   5760
   End
   Begin VB.Line Line6 
      X1              =   1920
      X2              =   840
      Y1              =   4920
      Y2              =   5760
   End
   Begin VB.Line Line5 
      X1              =   3360
      X2              =   4680
      Y1              =   4920
      Y2              =   4920
   End
   Begin VB.Line Line4 
      X1              =   4680
      X2              =   4680
      Y1              =   840
      Y2              =   4920
   End
   Begin VB.Line Line3 
      X1              =   720
      X2              =   1920
      Y1              =   4920
      Y2              =   4920
   End
   Begin VB.Line Line2 
      X1              =   4680
      X2              =   720
      Y1              =   840
      Y2              =   840
   End
   Begin VB.Line Line1 
      X1              =   720
      X2              =   720
      Y1              =   840
      Y2              =   4920
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim ballCount As Integer
Dim ballDrawn As Integer

Dim radius As Double
Dim angle  As Double

Dim xBall  As Double
Dim yBall  As Double

Dim xGlobalBall  As Double
Dim yGlobalBall  As Double


Private Sub drawButoon_Click()

    ' Clear all the balls
    For i = 0 To 7
        golfBall(i).BackStyle = 0
        golfBall(i).BackColor = &H80FF&
    Next
    
    ' Reset the count
    ballCount = 0
     
    While ballCount <= 4
        
        ' Draw a ball
        ballDrawn = Rand(0, 7)
    
        ' Check if the ball has been previously set
        If golfBall(ballDrawn).BackStyle = 0 Then
        
            'Set the drawn ball
            golfBall(ballDrawn).BackStyle = 1
            
            ' Increment the count
            ballCount = ballCount + 1
        
        End If
    
    Wend
    
    ' Reset the count
    ballCount = 0
     
    While ballCount <= 1
        
        ' Draw a ball
        ballDrawn = Rand(0, 7)
        
        If golfBall(ballDrawn).BackColor <> &HFFFF00 Then
            ' Check if the ball has been previously set
            If golfBall(ballDrawn).BackStyle = 1 Then
            
                'Set the drawn ball
                golfBall(ballDrawn).BackColor = &HFFFF00
            
                ' Increment the count
                ballCount = ballCount + 1
        
            End If
        End If
    
    Wend
    
End Sub

Private Sub drawCanButton_Click()
                
    ' Clear all the balls
    For i = 0 To 5
        can(i).BackStyle = 0
    Next
    
    ' Reset the count
    ballCount = 0
      
    ' Draw a ball
    ballDrawn = Rand(0, 5)

    'Set the drawn ball
    can(ballDrawn).BackStyle = 1

       
        ' Draw a radius to locate the ball
'        radius = Rand(1000 + 2 * can.Width, 2000 - 2 * can.Width)
        
        ' Temp save the higher limite
 '       higherAngle = 2 * 3.1415926535
        
        ' Draw an angle to locate the ball
  '      angle = Rand(0, higherAngle)
        
        ' Generate the location of the ball from the center of the ball region
   '     xBall = radius * Cos(angle)
     '   yBall = radius * Sin(angle)
    
        ' Set the ball global coordinates
   '     xGlobalBall = internalBallArea.Left + internalBallArea.Width / 2 - can.Width
    '    yGlobalBall = internalBallArea.Top + internalBallArea.Height / 2 - can.Height
        
        ' Set the can postions
    '    can.Left = xGlobalBall + xBall
     '   can.Top = yGlobalBall + yBall
        
        ' Show the can
      '  can.Visible = True
        
End Sub

Private Sub Form_Load()
    
    ' Initialize variables
    ballCount = 0
    
    'Initialize the random # generator.
    Randomize
    
    ' Clear all the balls
    For i = 0 To 7
        golfBall(i).BackStyle = 0
    Next
    
    ' Clear all the balls
    For i = 0 To 5
        can(i).BackStyle = 0
    Next
    
End Sub

'===============================================
'Rand - Return a random number in a given range.
'
'Parameters:
'  Low  - The lower bounds of the range.
'  High - The upper bounds of the range.
'
'Returns:
'  Returns a random number from Low..High.
'===============================================

Public Function Rand(ByVal Low As Double, _
                     ByVal High As Double) As Double
  Rand = Int((High - Low + 1) * Rnd) + Low
End Function

