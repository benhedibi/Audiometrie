object TympPrevFrm: TTympPrevFrm
  Left = 0
  Top = 0
  ActiveControl = GroupBox2
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Tympanogramme'
  ClientHeight = 674
  ClientWidth = 922
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object ImpLbl: TLabel
    Left = 548
    Top = 564
    Width = 70
    Height = 18
    Cursor = crHandPoint
    Caption = 'Imprimer'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = PrintImgClick
    OnMouseEnter = ImpLblMouseEnter
    OnMouseLeave = ImpLblMouseLeave
  end
  object PrintImg: TImage
    Left = 565
    Top = 530
    Width = 32
    Height = 32
    Cursor = crHandPoint
    AutoSize = True
    Picture.Data = {
      0954506E67496D61676589504E470D0A1A0A0000000D49484452000000200000
      00200806000000737A7AF4000000017352474200AECE1CE90000000467414D41
      0000B18F0BFC6105000000097048597300000EC300000EC301C76FA864000002
      0F4944415478DA63641860C038EA007C92FD277FE4313232DA5062C1FFFFFF8F
      149A734C22CF01A77E2C6564608CA2C8010CFF97159A71448F3A60E839C0C9C9
      E9BF514419838C812325F6333CB9B09FE1DC8A2E867DFBF661B56B7039202929
      C9EEDFBF7F9380594F07C865A6C8664CF017882F03B365DE82050B0E63382039
      39590868F91D205390CA16A383F73F7FFE545EB66CD97B1407242626FA00A9CD
      B4B27543AE2083EDBA2F0CC24F7F330043D867DEBC795B511C90909010059458
      4A2B07BC9566651078F19B81F92FB8748C0646C332BA3A00190C4E07444444E4
      022526916F2CF100E8D1BC152B564C4671809B9B5BEE9F3F7FE8E200161696BC
      5DBB76A13AC0D1D191AE51B07FFF7ED4284077C0A74F9F187EFDFA45150BD9D8
      D818F8F8F84873C093274F188482DA18B8743D29B2FCDBE5ED0CEFD65531C8C8
      C890E680DFBF7F3348BBA43270CB6A53E480AF8FAF323CDD339B81959515BF03
      1C1C1CAC9998988E206B46AE8C3E7DFBC3F0ECDD77A22DD690E1858424B43242
      06400758031D700CC501F6F6F62C40071C0386822936075C7BFC8961F3C9E744
      3BA03C441D97034E0A0B0B5BAF5EBDFA2F8A0340C0CACA8A97838303541EE802
      1DC26C99D2662EAA6228474914BCBE73FED1F13955278166822CBC04CC829376
      EFDEFD15264F748BE8C99B6F0C67EF7CC06B99B18A00838C08176A7053AB4936
      E00E201750E68081EE98D0038C3A00003A5923308CEE66340000000049454E44
      AE426082}
    OnClick = PrintImgClick
    OnMouseEnter = PrintImgMouseEnter
    OnMouseLeave = PrintImgMouseLeave
  end
  object PreviewImg: TImage
    Left = 678
    Top = 530
    Width = 32
    Height = 32
    Cursor = crHandPoint
    AutoSize = True
    Picture.Data = {
      0954506E67496D61676589504E470D0A1A0A0000000D49484452000000200000
      00200806000000737A7AF4000000017352474200AECE1CE90000000467414D41
      0000B18F0BFC6105000000097048597300000EC300000EC301C76FA864000003
      674944415478DAE5976D48535118C7FF7757F752AE4C57A24E2B8A8A24122CB3
      22A4E8852492A24549501011F4A922D24F1154DF84F0536034A7F4426AAF7311
      C3226B99BD585161569BE66673CA36B7B9B7BBEDDE7566186DA9E8EEB2A0FFA7
      7BEF39E7B9BFF33CE7FCCFBD14FEB2A87F0AE0FCCBC02A8A0BE74E26809F166A
      2B5650CEC400BCF05FA140954D7470920008B2E156861695C40BC10B6079260D
      939383CDC3C50DC10B60A59C46865480D69E50DC10BC01E433050872881B2221
      0011C50B913080588863ABC46BFF38409A848244186D254116187073385A289A
      90C7F002184FFF0780DBFC19B60E1DBC163D825E1768A104E2B42CA42E2C40A7
      A65AD4D0D010E005D0AE77A0D7EA8D1A201050589F370356DD6538BBDE607AE6
      42CC98BB0CC929B3C0313EB82D06B8BADF820D32FA7038ACA8ADAD7D9B508045
      991224B55723E0B22277E34148E54B7E0B1AF438607CA8C290E9A39BE3B8B575
      7575EF125602736B236C1F9F227B5B05745F39905946B5971665FDB8087330A8
      AB30D4DBA9F7783C796395635C00F5F33E74985C3FDBCB56A76350731AD96B76
      436D998B7E87FFB780E5BB164765A2F3EA2970A1C0E19A9A9AEA4903986D3EB8
      7CA19F1D658ED730B7DD8474DB595CD79947CDD0AF0011199B95B07F7EDEAC52
      A936F1024811D340C71D308E3E2CD87E1C1395ED430B7A9F5C1B2019C8E05582
      05992928F46BC1067C98BFF5C88401EC9FDA607C50C3900C88270D10ABC80274
      7FFB843925276119F48FDA67895C1A753FF0FA3E29DBAD1E02306FD20051DB90
      F45C37DB0A93F6027214E770E991155CCC0E8828760DE86F57C2D3A7AF252538
      C00F80A868512A6C9A3390E6E4A14BB6056D9DF67101880FA0ABA90A1445152B
      95CAC7BC4B1091C3D08E1EED45E414EF832D351F2C179D859112308EFEE1D913
      8BBE45D2BF73AC78719D05FDAF34B0BC54237DE93A6414940CDBF0883836083B
      312ACB8BBB60196F3779242566B58140BC4F1840444E03F184678D08B8072149
      9743284D43C8EF85CF6A2426C822CC862A49EA69F2F2630E2FE36242C143F76E
      34D4270C2022F21252E70EB2C8BE20E07122493C8D9C86D998393F1F278A65C3
      B177ED2D5399EC9EFDE40C0BCF9A2EDC130B3125DF039B4A15CF5CFE40D16810
      53F66B3616C494FE1B8E408893695B4BD34DD9940344B47987A25E448BCAD58D
      97BBFF0A40ACBE0313EB133F86688F200000000049454E44AE426082}
    OnClick = PreviewImgClick
    OnMouseEnter = PreviewImgMouseEnter
    OnMouseLeave = PreviewImgMouseLeave
  end
  object PreviewLbl: TLabel
    Left = 668
    Top = 564
    Width = 52
    Height = 18
    Cursor = crHandPoint
    Caption = 'Aper'#231'u'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = PreviewImgClick
    OnMouseEnter = ImpLblMouseEnter
    OnMouseLeave = ImpLblMouseLeave
  end
  object CancelImg: TImage
    Left = 791
    Top = 530
    Width = 32
    Height = 32
    Cursor = crHandPoint
    AutoSize = True
    Picture.Data = {
      0954506E67496D61676589504E470D0A1A0A0000000D49484452000000200000
      00200806000000737A7AF4000000017352474200AECE1CE90000000467414D41
      0000B18F0BFC6105000000097048597300000EC300000EC301C76FA864000001
      DE4944415478DAED97CF4B025110C7BF4F098AC0AE15D1A922FC55740BBAF923
      A1A374A93F20BC08E1AD5BF40F0441A7203C1404950845B8160681D02508378B
      08840E415E8B20C89D6615C3F2D7BAE686E11C761F6FDEBCF779F366E6ED0AFC
      B1880E407B0124933D78B3CCC16DDF371E40BA1D84F888B0C503DC8E4563014E
      D3532025CAA38700DA3516209EF2438830B77A0B1D460110099CC92B20AC3140
      C938230012996EE45EB7585D61217A64A8CB2AF3651936830FE5183EE79D3E80
      84DC8F1C0EB935DDE4E6CE0153086EEB957680983C093345B97BB8C9C58BDE7A
      678F04E0B26FFF1180CA40C4CF79781C07F50154F9BD2328857881A051B89DCF
      F501F2103A82500833EBC65867FB9E355F761B9C3D416D00056A7D6928A56661
      127BDCEAFBA1C9E2C2368055A16803288A9E4224A5020CB159D6AFE49CF04EA4
      1A0350A5D1527C921E4097F2540E403E781DB1C601F2BB6AE0326A09802A5AAF
      E36A4720841D2EDB8D7E002D12977D9C721C84C2F243A33308EB2F38C37111CC
      A721D138BFAD15C711D6E1B12F9739A56900495E80093B35C7A88548C98D6076
      326B3C805A8A05F9B90A462AA95B0CC097118925767DB89A790B01E88C670FC1
      E5B8AE65FE7B415810BE6CF88304A62378ACF75ACCDBECBFA003F01F013E0117
      46C521B0CF92DC0000000049454E44AE426082}
    OnClick = CancelImgClick
    OnMouseEnter = CancelImgMouseEnter
    OnMouseLeave = CancelImgMouseLeave
  end
  object CancelLbl: TLabel
    Left = 780
    Top = 564
    Width = 58
    Height = 18
    Cursor = crHandPoint
    Caption = 'Annuler'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = CancelImgClick
    OnMouseEnter = ImpLblMouseEnter
    OnMouseLeave = ImpLblMouseLeave
  end
  object GroupBox4: TGroupBox
    Left = 20
    Top = 20
    Width = 429
    Height = 493
    Caption = '  Oreille Droite  '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    object Label58: TLabel
      Left = 134
      Top = 406
      Width = 160
      Height = 18
      Caption = '&R'#233'flexes stap'#233'diens :'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object OdShape1: TShape
      Left = 24
      Top = 351
      Width = 8
      Height = 8
      Brush.Color = clHotLight
      Visible = False
    end
    object OdTympDate1Lbl: TLabel
      Left = 38
      Top = 348
      Width = 3
      Height = 13
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object OdTympDate2Lbl: TLabel
      Left = 245
      Top = 348
      Width = 3
      Height = 13
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object OdShape2: TShape
      Left = 231
      Top = 351
      Width = 8
      Height = 8
      Brush.Color = clRed
      Visible = False
    end
    object OdRsEdit1: TEdit
      Left = 85
      Top = 455
      Width = 65
      Height = 22
      Alignment = taCenter
      BevelInner = bvLowered
      BevelKind = bkSoft
      BevelOuter = bvNone
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      MaxLength = 3
      NumbersOnly = True
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
      Text = '0'
    end
    object OdRsEdit2: TEdit
      Left = 149
      Top = 455
      Width = 65
      Height = 22
      Alignment = taCenter
      BevelInner = bvLowered
      BevelKind = bkSoft
      BevelOuter = bvNone
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      MaxLength = 3
      NumbersOnly = True
      ParentFont = False
      ReadOnly = True
      TabOrder = 1
      Text = '0'
    end
    object OdRsEdit3: TEdit
      Left = 214
      Top = 455
      Width = 65
      Height = 22
      Alignment = taCenter
      BevelInner = bvLowered
      BevelKind = bkSoft
      BevelOuter = bvNone
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      MaxLength = 3
      NumbersOnly = True
      ParentFont = False
      ReadOnly = True
      TabOrder = 2
      Text = '0'
    end
    object OdRsEdit4: TEdit
      Left = 279
      Top = 455
      Width = 64
      Height = 22
      Alignment = taCenter
      BevelInner = bvLowered
      BevelKind = bkSoft
      BevelOuter = bvNone
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      MaxLength = 3
      NumbersOnly = True
      ParentFont = False
      ReadOnly = True
      TabOrder = 3
      Text = '0'
    end
    object Panel79: TPanel
      Left = 85
      Top = 432
      Width = 66
      Height = 21
      BevelKind = bkTile
      BevelOuter = bvNone
      Caption = '500 hz'
      Color = clBlack
      Font.Charset = ANSI_CHARSET
      Font.Color = clWhite
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsBold]
      ParentBackground = False
      ParentFont = False
      TabOrder = 7
    end
    object Panel78: TPanel
      Left = 150
      Top = 432
      Width = 66
      Height = 21
      BevelKind = bkTile
      BevelOuter = bvNone
      Caption = '1000 hz'
      Color = clBlack
      Font.Charset = ANSI_CHARSET
      Font.Color = clWhite
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsBold]
      ParentBackground = False
      ParentFont = False
      TabOrder = 6
    end
    object Panel77: TPanel
      Left = 215
      Top = 432
      Width = 65
      Height = 21
      BevelKind = bkTile
      BevelOuter = bvNone
      Caption = '2000 hz'
      Color = clBlack
      Font.Charset = ANSI_CHARSET
      Font.Color = clWhite
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsBold]
      ParentBackground = False
      ParentFont = False
      TabOrder = 5
    end
    object Panel76: TPanel
      Left = 279
      Top = 432
      Width = 65
      Height = 21
      BevelKind = bkTile
      BevelOuter = bvNone
      Caption = '4000 hz'
      Color = clBlack
      Font.Charset = ANSI_CHARSET
      Font.Color = clWhite
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsBold]
      ParentBackground = False
      ParentFont = False
      TabOrder = 4
    end
    object Chart1: TChart
      Left = 38
      Top = 41
      Width = 349
      Height = 288
      AllowPanning = pmNone
      BackWall.Brush.Gradient.Direction = gdBottomTop
      BackWall.Brush.Gradient.EndColor = clWhite
      BackWall.Brush.Gradient.StartColor = 15395562
      BackWall.Brush.Gradient.Visible = True
      BackWall.Transparent = False
      BackWall.Visible = False
      Border.Color = clSilver
      Border.Visible = True
      BottomWall.Visible = False
      Foot.Font.Color = clBlue
      Foot.Font.Name = 'Verdana'
      Gradient.Direction = gdBottomTop
      Gradient.EndColor = clWhite
      Gradient.MidColor = 15395562
      Gradient.StartColor = 15395562
      LeftWall.Color = 14745599
      Legend.Font.Name = 'Verdana'
      Legend.Shadow.Transparency = 0
      Legend.Visible = False
      RightWall.Color = 14745599
      Title.Font.Name = 'Verdana'
      Title.Text.Strings = (
        'TChart')
      Title.Visible = False
      AxisBehind = False
      BottomAxis.Automatic = False
      BottomAxis.AutomaticMaximum = False
      BottomAxis.AutomaticMinimum = False
      BottomAxis.Axis.Color = 4210752
      BottomAxis.Axis.Width = 1
      BottomAxis.Axis.EndStyle = esRound
      BottomAxis.Axis.Fill.Gradient.Balance = 41
      BottomAxis.Grid.Color = 11119017
      BottomAxis.Increment = 100.000000000000000000
      BottomAxis.LabelsFormat.Font.Name = 'Verdana'
      BottomAxis.Maximum = 300.000000000000000000
      BottomAxis.Minimum = -300.000000000000000000
      BottomAxis.MinimumOffset = -1
      BottomAxis.TicksInner.Color = 11119017
      BottomAxis.Title.Font.Name = 'Verdana'
      DepthAxis.Automatic = False
      DepthAxis.AutomaticMaximum = False
      DepthAxis.AutomaticMinimum = False
      DepthAxis.Axis.Color = 4210752
      DepthAxis.Grid.Color = 11119017
      DepthAxis.Increment = 1.000000000000000000
      DepthAxis.LabelsFormat.Font.Name = 'Verdana'
      DepthAxis.Maximum = 5.000000000000000000
      DepthAxis.TicksInner.Color = 11119017
      DepthAxis.Title.Font.Name = 'Verdana'
      DepthTopAxis.Automatic = False
      DepthTopAxis.AutomaticMaximum = False
      DepthTopAxis.AutomaticMinimum = False
      DepthTopAxis.Axis.Color = 4210752
      DepthTopAxis.Grid.Color = 11119017
      DepthTopAxis.LabelsFormat.Font.Name = 'Verdana'
      DepthTopAxis.Maximum = 0.500000000000000000
      DepthTopAxis.Minimum = -0.500000000000000000
      DepthTopAxis.TicksInner.Color = 11119017
      DepthTopAxis.Title.Font.Name = 'Verdana'
      LeftAxis.Automatic = False
      LeftAxis.AutomaticMaximum = False
      LeftAxis.AutomaticMinimum = False
      LeftAxis.Axis.Color = 4210752
      LeftAxis.Grid.Color = 16744703
      LeftAxis.Grid.Style = psDash
      LeftAxis.Increment = 1.000000000000000000
      LeftAxis.LabelsFormat.Font.Name = 'Verdana'
      LeftAxis.Maximum = 5.000000000000000000
      LeftAxis.MaximumOffset = -1
      LeftAxis.TicksInner.Color = 11119017
      LeftAxis.Title.Font.Name = 'Verdana'
      LeftAxis.Title.Visible = False
      Panning.MouseWheel = pmwNone
      RightAxis.Automatic = False
      RightAxis.AutomaticMaximum = False
      RightAxis.AutomaticMinimum = False
      RightAxis.Axis.Color = 4210752
      RightAxis.Axis.Visible = False
      RightAxis.Grid.Color = 16744703
      RightAxis.Grid.Style = psDash
      RightAxis.Increment = 1.000000000000000000
      RightAxis.Labels = False
      RightAxis.LabelsFormat.Font.Name = 'Verdana'
      RightAxis.LabelsFormat.Visible = False
      RightAxis.LabelsOnAxis = False
      RightAxis.Maximum = 5.000000000000000000
      RightAxis.TicksInner.Color = 11119017
      RightAxis.Title.Font.Name = 'Verdana'
      RightAxis.Title.Visible = False
      RightAxis.Visible = False
      TopAxis.Automatic = False
      TopAxis.AutomaticMaximum = False
      TopAxis.AutomaticMinimum = False
      TopAxis.Axis.Color = 4210752
      TopAxis.Grid.Color = 11119017
      TopAxis.LabelsFormat.Font.Name = 'Verdana'
      TopAxis.TicksInner.Color = 11119017
      TopAxis.Title.Font.Name = 'Verdana'
      TopAxis.Visible = False
      View3D = False
      Zoom.Allow = False
      BevelOuter = bvNone
      Color = clWhite
      TabOrder = 8
      DefaultCanvas = 'TTeeCanvas3D'
      ColorPaletteIndex = 13
      object LineSeries2: TLineSeries
        HoverElement = [heCurrent]
        Legend.Visible = False
        SeriesColor = 16744448
        ShowInLegend = False
        Brush.BackColor = clDefault
        ClickableLine = False
        LinePen.Width = 2
        Pointer.InflateMargins = True
        Pointer.Style = psRectangle
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
        Data = {0000000000}
        Detail = {0000000000}
      end
      object LineSeries3: TLineSeries
        HoverElement = [heCurrent]
        Legend.Visible = False
        Active = False
        SeriesColor = clRed
        ShowInLegend = False
        Brush.BackColor = clDefault
        ClickableLine = False
        LinePen.Width = 2
        Pointer.InflateMargins = True
        Pointer.Style = psRectangle
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
        Data = {0000000000}
      end
    end
  end
  object GroupBox1: TGroupBox
    Left = 472
    Top = 20
    Width = 429
    Height = 493
    Caption = '  Oreille Gauche  '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    object Label1: TLabel
      Left = 142
      Top = 406
      Width = 160
      Height = 18
      Caption = '&R'#233'flexes stap'#233'diens :'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object OgTympDate1Lbl: TLabel
      Left = 38
      Top = 348
      Width = 3
      Height = 13
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object OgShape1: TShape
      Left = 24
      Top = 351
      Width = 8
      Height = 8
      Brush.Color = clHotLight
      Visible = False
    end
    object OgShape2: TShape
      Left = 231
      Top = 351
      Width = 8
      Height = 8
      Brush.Color = clRed
      Visible = False
    end
    object OgTympDate2Lbl: TLabel
      Left = 245
      Top = 348
      Width = 3
      Height = 13
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object OgRsEdit1: TEdit
      Left = 93
      Top = 455
      Width = 65
      Height = 22
      Alignment = taCenter
      BevelInner = bvLowered
      BevelKind = bkSoft
      BevelOuter = bvNone
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      MaxLength = 3
      NumbersOnly = True
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
      Text = '0'
    end
    object OgRsEdit2: TEdit
      Left = 157
      Top = 455
      Width = 65
      Height = 22
      Alignment = taCenter
      BevelInner = bvLowered
      BevelKind = bkSoft
      BevelOuter = bvNone
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      MaxLength = 3
      NumbersOnly = True
      ParentFont = False
      ReadOnly = True
      TabOrder = 1
      Text = '0'
    end
    object OgRsEdit3: TEdit
      Left = 222
      Top = 455
      Width = 65
      Height = 22
      Alignment = taCenter
      BevelInner = bvLowered
      BevelKind = bkSoft
      BevelOuter = bvNone
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      MaxLength = 3
      NumbersOnly = True
      ParentFont = False
      ReadOnly = True
      TabOrder = 2
      Text = '0'
    end
    object OgRsEdit4: TEdit
      Left = 287
      Top = 455
      Width = 64
      Height = 22
      Alignment = taCenter
      BevelInner = bvLowered
      BevelKind = bkSoft
      BevelOuter = bvNone
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      MaxLength = 3
      NumbersOnly = True
      ParentFont = False
      ReadOnly = True
      TabOrder = 3
      Text = '0'
    end
    object Panel1: TPanel
      Left = 93
      Top = 432
      Width = 66
      Height = 21
      BevelKind = bkTile
      BevelOuter = bvNone
      Caption = '500 hz'
      Color = clBlack
      Font.Charset = ANSI_CHARSET
      Font.Color = clWhite
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsBold]
      ParentBackground = False
      ParentFont = False
      TabOrder = 7
    end
    object Panel2: TPanel
      Left = 158
      Top = 432
      Width = 66
      Height = 21
      BevelKind = bkTile
      BevelOuter = bvNone
      Caption = '1000 hz'
      Color = clBlack
      Font.Charset = ANSI_CHARSET
      Font.Color = clWhite
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsBold]
      ParentBackground = False
      ParentFont = False
      TabOrder = 6
    end
    object Panel3: TPanel
      Left = 223
      Top = 432
      Width = 65
      Height = 21
      BevelKind = bkTile
      BevelOuter = bvNone
      Caption = '2000 hz'
      Color = clBlack
      Font.Charset = ANSI_CHARSET
      Font.Color = clWhite
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsBold]
      ParentBackground = False
      ParentFont = False
      TabOrder = 5
    end
    object Panel4: TPanel
      Left = 287
      Top = 432
      Width = 65
      Height = 21
      BevelKind = bkTile
      BevelOuter = bvNone
      Caption = '4000 hz'
      Color = clBlack
      Font.Charset = ANSI_CHARSET
      Font.Color = clWhite
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsBold]
      ParentBackground = False
      ParentFont = False
      TabOrder = 4
    end
    object Chart2: TChart
      Left = 40
      Top = 41
      Width = 349
      Height = 288
      AllowPanning = pmNone
      BackWall.Brush.Gradient.Direction = gdBottomTop
      BackWall.Brush.Gradient.EndColor = clWhite
      BackWall.Brush.Gradient.StartColor = 15395562
      BackWall.Brush.Gradient.Visible = True
      BackWall.Transparent = False
      BackWall.Visible = False
      Border.Color = clSilver
      Border.Visible = True
      BottomWall.Visible = False
      Foot.Font.Color = clBlue
      Foot.Font.Name = 'Verdana'
      Gradient.Direction = gdBottomTop
      Gradient.EndColor = clWhite
      Gradient.MidColor = 15395562
      Gradient.StartColor = 15395562
      LeftWall.Color = 14745599
      Legend.Font.Name = 'Verdana'
      Legend.Shadow.Transparency = 0
      Legend.Visible = False
      RightWall.Color = 14745599
      Title.Font.Name = 'Verdana'
      AxisBehind = False
      BottomAxis.Automatic = False
      BottomAxis.AutomaticMaximum = False
      BottomAxis.AutomaticMinimum = False
      BottomAxis.Axis.Color = 4210752
      BottomAxis.Axis.Width = 1
      BottomAxis.Axis.EndStyle = esRound
      BottomAxis.Axis.Fill.Gradient.Balance = 41
      BottomAxis.Grid.Color = 11119017
      BottomAxis.Increment = 100.000000000000000000
      BottomAxis.LabelsFormat.Font.Name = 'Verdana'
      BottomAxis.Maximum = 300.000000000000000000
      BottomAxis.Minimum = -300.000000000000000000
      BottomAxis.MinimumOffset = -1
      BottomAxis.TicksInner.Color = 11119017
      BottomAxis.Title.Font.Name = 'Verdana'
      DepthAxis.Automatic = False
      DepthAxis.AutomaticMaximum = False
      DepthAxis.AutomaticMinimum = False
      DepthAxis.Axis.Color = 4210752
      DepthAxis.Grid.Color = 11119017
      DepthAxis.Increment = 1.000000000000000000
      DepthAxis.LabelsFormat.Font.Name = 'Verdana'
      DepthAxis.Maximum = 5.000000000000000000
      DepthAxis.TicksInner.Color = 11119017
      DepthAxis.Title.Font.Name = 'Verdana'
      DepthTopAxis.Automatic = False
      DepthTopAxis.AutomaticMaximum = False
      DepthTopAxis.AutomaticMinimum = False
      DepthTopAxis.Axis.Color = 4210752
      DepthTopAxis.Grid.Color = 11119017
      DepthTopAxis.LabelsFormat.Font.Name = 'Verdana'
      DepthTopAxis.Maximum = 0.500000000000000000
      DepthTopAxis.Minimum = -0.500000000000000000
      DepthTopAxis.TicksInner.Color = 11119017
      DepthTopAxis.Title.Font.Name = 'Verdana'
      LeftAxis.Automatic = False
      LeftAxis.AutomaticMaximum = False
      LeftAxis.AutomaticMinimum = False
      LeftAxis.Axis.Color = 4210752
      LeftAxis.Grid.Color = 16744703
      LeftAxis.Grid.Style = psDash
      LeftAxis.Increment = 1.000000000000000000
      LeftAxis.LabelsFormat.Font.Name = 'Verdana'
      LeftAxis.Maximum = 5.000000000000000000
      LeftAxis.MaximumOffset = -1
      LeftAxis.TicksInner.Color = 11119017
      LeftAxis.Title.Font.Name = 'Verdana'
      LeftAxis.Title.Visible = False
      Panning.MouseWheel = pmwNone
      RightAxis.Automatic = False
      RightAxis.AutomaticMaximum = False
      RightAxis.AutomaticMinimum = False
      RightAxis.Axis.Color = 4210752
      RightAxis.Axis.Visible = False
      RightAxis.Grid.Color = 16744703
      RightAxis.Grid.Style = psDash
      RightAxis.Increment = 1.000000000000000000
      RightAxis.Labels = False
      RightAxis.LabelsFormat.Font.Name = 'Verdana'
      RightAxis.LabelsFormat.Visible = False
      RightAxis.LabelsOnAxis = False
      RightAxis.Maximum = 5.000000000000000000
      RightAxis.TicksInner.Color = 11119017
      RightAxis.Title.Font.Name = 'Verdana'
      RightAxis.Title.Visible = False
      RightAxis.Visible = False
      TopAxis.Automatic = False
      TopAxis.AutomaticMaximum = False
      TopAxis.AutomaticMinimum = False
      TopAxis.Axis.Color = 4210752
      TopAxis.Grid.Color = 11119017
      TopAxis.LabelsFormat.Font.Name = 'Verdana'
      TopAxis.TicksInner.Color = 11119017
      TopAxis.Title.Font.Name = 'Verdana'
      TopAxis.Visible = False
      View3D = False
      Zoom.Allow = False
      BevelOuter = bvNone
      Color = clWhite
      TabOrder = 8
      DefaultCanvas = 'TTeeCanvas3D'
      ColorPaletteIndex = 13
      object LineSeries1: TLineSeries
        HoverElement = [heCurrent]
        Legend.Visible = False
        SeriesColor = 16744448
        ShowInLegend = False
        Brush.BackColor = clDefault
        ClickableLine = False
        DrawStyle = dsCurve
        LinePen.Width = 2
        Pointer.InflateMargins = True
        Pointer.Style = psVisual
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
        object TSmoothingFunction
          Period = 1.000000000000000000
          Factor = 8
        end
      end
      object Series3: TLineSeries
        HoverElement = [heCurrent]
        Legend.Visible = False
        Active = False
        SeriesColor = clRed
        ShowInLegend = False
        Brush.BackColor = clDefault
        ClickableLine = False
        LinePen.Width = 2
        Pointer.InflateMargins = True
        Pointer.Style = psRectangle
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
        Data = {0000000000}
        Detail = {0000000000}
      end
    end
  end
  object GroupBox2: TGroupBox
    Left = 20
    Top = 530
    Width = 429
    Height = 126
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    object Label2: TLabel
      Left = 25
      Top = 15
      Width = 135
      Height = 14
      Caption = 'Nom Pr'#233'nom Patient :'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label3: TLabel
      Left = 72
      Top = 34
      Width = 88
      Height = 14
      Caption = 'Code Patient :'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label4: TLabel
      Left = 49
      Top = 53
      Width = 111
      Height = 14
      Caption = 'M'#233'decin Traitant :'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label5: TLabel
      Left = 52
      Top = 73
      Width = 108
      Height = 14
      Caption = 'Date Impression :'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label6: TLabel
      Left = 90
      Top = 93
      Width = 70
      Height = 14
      Caption = 'Op'#233'rateur :'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object NomLbl: TLabel
      Left = 166
      Top = 15
      Width = 4
      Height = 14
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object CodepLbl: TLabel
      Left = 166
      Top = 34
      Width = 4
      Height = 14
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlue
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object MedLbl: TLabel
      Left = 166
      Top = 53
      Width = 4
      Height = 14
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object DateImpLbl: TLabel
      Left = 166
      Top = 73
      Width = 4
      Height = 14
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlue
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object OpLbl: TLabel
      Left = 166
      Top = 93
      Width = 4
      Height = 14
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
  end
end
