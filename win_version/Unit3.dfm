object MedInfoFrm: TMedInfoFrm
  Left = 0
  Top = 0
  BorderIcons = []
  BorderStyle = bsSingle
  ClientHeight = 580
  ClientWidth = 385
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label3: TLabel
    Left = 48
    Top = 542
    Width = 54
    Height = 18
    Cursor = crHandPoint
    Caption = '&Valider'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = Label3Click
    OnMouseEnter = Label4MouseEnter
    OnMouseLeave = Label4MouseLeave
  end
  object Label4: TLabel
    Left = 279
    Top = 542
    Width = 58
    Height = 18
    Cursor = crHandPoint
    Caption = '&Annuler'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = Label4Click
    OnMouseEnter = Label4MouseEnter
    OnMouseLeave = Label4MouseLeave
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 369
    Height = 513
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    object Label1: TLabel
      Left = 24
      Top = 80
      Width = 39
      Height = 13
      Caption = '&Pays :'
    end
    object Label2: TLabel
      Left = 24
      Top = 141
      Width = 90
      Height = 13
      Caption = '&Gouvernorat :'
    end
    object NomEdit: TLabeledEdit
      Left = 24
      Top = 36
      Width = 305
      Height = 21
      EditLabel.Width = 37
      EditLabel.Height = 13
      EditLabel.Caption = '&Nom :'
      MaxLength = 24
      TabOrder = 0
    end
    object PaysCombo: TComboBox
      Left = 24
      Top = 101
      Width = 305
      Height = 21
      TabOrder = 1
      OnSelect = PaysComboSelect
    end
    object GouvCombo: TComboBox
      Left = 24
      Top = 160
      Width = 305
      Height = 21
      TabOrder = 2
      TextHint = 'Uniquement pour la Tunisie'
    end
    object Tel1Edit: TLabeledEdit
      Left = 24
      Top = 316
      Width = 305
      Height = 21
      EditLabel.Width = 88
      EditLabel.Height = 13
      EditLabel.Caption = 'T'#233'l'#233'phone 1 :'
      MaxLength = 16
      TabOrder = 3
    end
    object Tel2Edit: TLabeledEdit
      Left = 24
      Top = 364
      Width = 305
      Height = 21
      EditLabel.Width = 88
      EditLabel.Height = 13
      EditLabel.Caption = 'T'#233'l'#233'phone 2 :'
      MaxLength = 16
      TabOrder = 4
    end
    object FaxEdit: TLabeledEdit
      Left = 24
      Top = 412
      Width = 305
      Height = 21
      EditLabel.Width = 32
      EditLabel.Height = 13
      EditLabel.Caption = '&Fax :'
      MaxLength = 16
      TabOrder = 5
    end
    object MailEdit: TLabeledEdit
      Left = 24
      Top = 460
      Width = 305
      Height = 21
      EditLabel.Width = 50
      EditLabel.Height = 13
      EditLabel.Caption = '&E-mail :'
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsBold]
      MaxLength = 32
      ParentFont = False
      TabOrder = 6
      OnKeyPress = MailEditKeyPress
    end
    object PriveRadio: TRadioButton
      Left = 24
      Top = 208
      Width = 113
      Height = 17
      Caption = 'M'#233'decin Priv'#233
      Checked = True
      TabOrder = 7
      TabStop = True
    end
    object CliniqueRadio: TRadioButton
      Left = 24
      Top = 231
      Width = 113
      Height = 17
      Caption = 'Clinique'
      TabOrder = 8
    end
    object HopitalRadio: TRadioButton
      Left = 24
      Top = 254
      Width = 113
      Height = 17
      Caption = 'H'#244'pital'
      TabOrder = 9
    end
  end
end
