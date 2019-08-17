object AudiogPrevFrm: TAudiogPrevFrm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Audiogramme'
  ClientHeight = 621
  ClientWidth = 842
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PrintImg: TImage
    Left = 498
    Top = 539
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
  object ImpLbl: TLabel
    Left = 481
    Top = 573
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
    OnMouseEnter = CancelLblMouseEnter
    OnMouseLeave = CancelLblMouseLeave
  end
  object PreviewLbl: TLabel
    Left = 601
    Top = 573
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
    OnMouseEnter = CancelLblMouseEnter
    OnMouseLeave = CancelLblMouseLeave
  end
  object PreviewImg: TImage
    Left = 611
    Top = 539
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
  object CancelImg: TImage
    Left = 724
    Top = 539
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
    Left = 713
    Top = 573
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
    OnMouseEnter = CancelLblMouseEnter
    OnMouseLeave = CancelLblMouseLeave
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 386
    Width = 405
    Height = 126
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
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
  object GroupBox1: TGroupBox
    Left = 8
    Top = 16
    Width = 405
    Height = 360
    Caption = '  Oreille Droite :  '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    object Shape1: TShape
      Left = 25
      Top = 336
      Width = 10
      Height = 10
      Brush.Color = clBlue
      Pen.Color = clBlue
    end
    object Label16: TLabel
      Left = 41
      Top = 333
      Width = 13
      Height = 13
      Caption = 'VA'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Shape2: TShape
      Left = 72
      Top = 336
      Width = 10
      Height = 10
      Brush.Color = clRed
      Pen.Color = clRed
    end
    object Label17: TLabel
      Left = 88
      Top = 333
      Width = 14
      Height = 13
      Caption = 'VO'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Shape3: TShape
      Left = 119
      Top = 336
      Width = 10
      Height = 10
      Brush.Color = clMaroon
      Pen.Color = clMaroon
    end
    object Label18: TLabel
      Left = 136
      Top = 334
      Width = 19
      Height = 13
      Caption = 'UCL'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object GainpGrphDateLbl: TLabel
      Left = 432
      Top = 25
      Width = 3
      Height = 13
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object OdVaShape: TShape
      Left = 175
      Top = 337
      Width = 10
      Height = 10
      Brush.Color = clGreen
      Pen.Color = clGreen
    end
    object OdVaDateLbl: TLabel
      Left = 192
      Top = 335
      Width = 3
      Height = 13
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object OdDateLbl: TLabel
      Left = 224
      Top = 35
      Width = 3
      Height = 13
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Chart1: TChart
      Left = 25
      Top = 54
      Width = 344
      Height = 267
      AllowPanning = pmNone
      BackWall.Brush.Gradient.Direction = gdBottomTop
      BackWall.Brush.Gradient.EndColor = clWhite
      BackWall.Brush.Gradient.StartColor = 15395562
      BackWall.Brush.Gradient.Visible = True
      BackWall.Transparent = False
      Border.Visible = True
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
      BottomAxis.Axis.Color = 4210752
      BottomAxis.Grid.Color = 11119017
      BottomAxis.LabelsFormat.Font.Name = 'Verdana'
      BottomAxis.TicksInner.Color = 11119017
      BottomAxis.Title.Font.Name = 'Verdana'
      DepthAxis.Axis.Color = 4210752
      DepthAxis.Grid.Color = 11119017
      DepthAxis.LabelsFormat.Font.Name = 'Verdana'
      DepthAxis.TicksInner.Color = 11119017
      DepthAxis.Title.Font.Name = 'Verdana'
      DepthTopAxis.Axis.Color = 4210752
      DepthTopAxis.Grid.Color = 11119017
      DepthTopAxis.LabelsFormat.Font.Name = 'Verdana'
      DepthTopAxis.TicksInner.Color = 11119017
      DepthTopAxis.Title.Font.Name = 'Verdana'
      LeftAxis.Automatic = False
      LeftAxis.AutomaticMaximum = False
      LeftAxis.AutomaticMinimum = False
      LeftAxis.Axis.Color = 4210752
      LeftAxis.Grid.Color = clFuchsia
      LeftAxis.Grid.Style = psDot
      LeftAxis.Inverted = True
      LeftAxis.LabelsFormat.Font.Name = 'Verdana'
      LeftAxis.Maximum = 120.000000000000000000
      LeftAxis.TickLength = 7
      LeftAxis.TicksInner.Color = 11119017
      LeftAxis.Title.Font.Name = 'Verdana'
      Panning.MouseWheel = pmwNone
      RightAxis.Axis.Color = 4210752
      RightAxis.Grid.Color = 11119017
      RightAxis.LabelsFormat.Font.Name = 'Verdana'
      RightAxis.TicksInner.Color = 11119017
      RightAxis.Title.Font.Name = 'Verdana'
      TopAxis.Automatic = False
      TopAxis.AutomaticMaximum = False
      TopAxis.AutomaticMinimum = False
      TopAxis.Axis.Color = 4210752
      TopAxis.Grid.Color = 11119017
      TopAxis.LabelsFormat.Font.Name = 'Verdana'
      TopAxis.Maximum = 11.000000000000000000
      TopAxis.TicksInner.Color = 11119017
      TopAxis.Title.Font.Name = 'Verdana'
      TopAxis.Items = {
        0F000000010454657874060231340556616C75650500000000000000E0024000
        010454657874060231330556616C75650500000000000000D002400001045465
        7874060231320556616C75650500000000000000C00240000104546578740602
        31320556616C75650500000000000000B0024000010454657874060138055661
        6C75650500000000000000A00240000104546578740601360556616C75650500
        000000000000900240000104546578740601340556616C756505000000000000
        00800240000104546578740601330556616C75650500000000000000E0014000
        0104546578740601320556616C75650500000000000000C00140000104546578
        740603312C350556616C75650500000000000000A00140000104546578740601
        310556616C75650500000000000000800140000104546578740604302C373505
        56616C75650500000000000000C00040000104546578740603302C350556616C
        75650500000000000000800040000104546578740604302C32350556616C7565
        050000000000000080FF3F0001045465787406013000}
      View3D = False
      View3DWalls = False
      BevelOuter = bvNone
      Color = clWhite
      TabOrder = 0
      DefaultCanvas = ''
      ColorPaletteIndex = 13
      object Series1: TLineSeries
        HoverElement = [heCurrent]
        Legend.Visible = False
        HorizAxis = aTopAxis
        SeriesColor = clBlue
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
      object Series2: TLineSeries
        HoverElement = [heCurrent]
        Legend.Visible = False
        HorizAxis = aTopAxis
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
      object Series3: TLineSeries
        HoverElement = [heCurrent]
        Legend.Visible = False
        HorizAxis = aTopAxis
        SeriesColor = clMaroon
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
      object Series4: TArrowSeries
        HoverElement = [heCurrent]
        Legend.Visible = False
        HorizAxis = aTopAxis
        Marks.Frame.Visible = False
        Marks.Transparent = True
        SeriesColor = clBlue
        ShowInLegend = False
        ClickableLine = False
        Pointer.InflateMargins = False
        Pointer.Pen.Width = 2
        Pointer.Style = psRectangle
        XValues.DateTime = False
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
        EndXValues.Name = 'EndX'
        EndXValues.Order = loNone
        EndYValues.Name = 'EndY'
        EndYValues.Order = loNone
        StartXValues.DateTime = False
        StartXValues.Name = 'X'
        StartXValues.Order = loAscending
        StartYValues.Name = 'Y'
        StartYValues.Order = loNone
        Data = {0000000000}
        Detail = {0000000000}
      end
      object Series5: TArrowSeries
        HoverElement = [heCurrent]
        Legend.Visible = False
        HorizAxis = aTopAxis
        Marks.Frame.Visible = False
        Marks.Transparent = True
        SeriesColor = clRed
        ShowInLegend = False
        ClickableLine = False
        Pointer.InflateMargins = False
        Pointer.Pen.Width = 2
        Pointer.Style = psRectangle
        XValues.DateTime = False
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
        EndXValues.Name = 'EndX'
        EndXValues.Order = loNone
        EndYValues.Name = 'EndY'
        EndYValues.Order = loNone
        StartXValues.DateTime = False
        StartXValues.Name = 'X'
        StartXValues.Order = loAscending
        StartYValues.Name = 'Y'
        StartYValues.Order = loNone
        Data = {0000000000}
        Detail = {0000000000}
      end
      object Series6: TArrowSeries
        HoverElement = [heCurrent]
        Legend.Visible = False
        HorizAxis = aTopAxis
        Marks.Frame.Visible = False
        Marks.Transparent = True
        SeriesColor = clMaroon
        ShowInLegend = False
        ClickableLine = False
        Pointer.InflateMargins = False
        Pointer.Pen.Width = 2
        Pointer.Style = psRectangle
        XValues.DateTime = False
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
        EndXValues.Name = 'EndX'
        EndXValues.Order = loNone
        EndYValues.Name = 'EndY'
        EndYValues.Order = loNone
        StartXValues.DateTime = False
        StartXValues.Name = 'X'
        StartXValues.Order = loAscending
        StartYValues.Name = 'Y'
        StartYValues.Order = loNone
        Data = {0000000000}
        Detail = {0000000000}
      end
      object Series7: TLineSeries
        HoverElement = [heCurrent]
        Legend.Visible = False
        HorizAxis = aTopAxis
        SeriesColor = clGreen
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
      object Series8: TArrowSeries
        HoverElement = [heCurrent]
        Legend.Visible = False
        HorizAxis = aTopAxis
        Marks.Frame.Visible = False
        Marks.Transparent = True
        SeriesColor = clGreen
        ShowInLegend = False
        ClickableLine = False
        Pointer.InflateMargins = False
        Pointer.Pen.Width = 2
        Pointer.Style = psRectangle
        XValues.DateTime = False
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
        EndXValues.Name = 'EndX'
        EndXValues.Order = loNone
        EndYValues.Name = 'EndY'
        EndYValues.Order = loNone
        StartXValues.DateTime = False
        StartXValues.Name = 'X'
        StartXValues.Order = loAscending
        StartYValues.Name = 'Y'
        StartYValues.Order = loNone
        Data = {0000000000}
      end
    end
  end
  object GroupBox3: TGroupBox
    Left = 426
    Top = 16
    Width = 405
    Height = 360
    Caption = '  Oreille Gauche :  '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    object Label9: TLabel
      Left = 432
      Top = 25
      Width = 3
      Height = 13
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Shape5: TShape
      Left = 25
      Top = 336
      Width = 10
      Height = 10
      Brush.Color = clBlue
      Pen.Color = clBlue
    end
    object Label7: TLabel
      Left = 41
      Top = 333
      Width = 13
      Height = 13
      Caption = 'VA'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Shape6: TShape
      Left = 72
      Top = 336
      Width = 10
      Height = 10
      Brush.Color = clRed
      Pen.Color = clRed
    end
    object Label8: TLabel
      Left = 88
      Top = 333
      Width = 14
      Height = 13
      Caption = 'VO'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Shape7: TShape
      Left = 119
      Top = 336
      Width = 10
      Height = 10
      Brush.Color = clMaroon
      Pen.Color = clMaroon
    end
    object Label10: TLabel
      Left = 136
      Top = 334
      Width = 19
      Height = 13
      Caption = 'UCL'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object OgVaShape: TShape
      Left = 175
      Top = 337
      Width = 10
      Height = 10
      Brush.Color = clGreen
      Pen.Color = clGreen
    end
    object OgVaDateLbl: TLabel
      Left = 192
      Top = 335
      Width = 3
      Height = 13
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object OgDateLbl: TLabel
      Left = 224
      Top = 35
      Width = 3
      Height = 13
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Chart2: TChart
      Left = 25
      Top = 54
      Width = 344
      Height = 267
      AllowPanning = pmNone
      BackWall.Brush.Gradient.Direction = gdBottomTop
      BackWall.Brush.Gradient.EndColor = clWhite
      BackWall.Brush.Gradient.StartColor = 15395562
      BackWall.Brush.Gradient.Visible = True
      BackWall.Transparent = False
      Border.Visible = True
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
      BottomAxis.Axis.Color = 4210752
      BottomAxis.Grid.Color = 11119017
      BottomAxis.LabelsFormat.Font.Name = 'Verdana'
      BottomAxis.TicksInner.Color = 11119017
      BottomAxis.Title.Font.Name = 'Verdana'
      DepthAxis.Axis.Color = 4210752
      DepthAxis.Grid.Color = 11119017
      DepthAxis.LabelsFormat.Font.Name = 'Verdana'
      DepthAxis.TicksInner.Color = 11119017
      DepthAxis.Title.Font.Name = 'Verdana'
      DepthTopAxis.Axis.Color = 4210752
      DepthTopAxis.Grid.Color = 11119017
      DepthTopAxis.LabelsFormat.Font.Name = 'Verdana'
      DepthTopAxis.TicksInner.Color = 11119017
      DepthTopAxis.Title.Font.Name = 'Verdana'
      LeftAxis.Automatic = False
      LeftAxis.AutomaticMaximum = False
      LeftAxis.AutomaticMinimum = False
      LeftAxis.Axis.Color = 4210752
      LeftAxis.Grid.Color = clFuchsia
      LeftAxis.Grid.Style = psDot
      LeftAxis.Inverted = True
      LeftAxis.LabelsFormat.Font.Name = 'Verdana'
      LeftAxis.Maximum = 120.000000000000000000
      LeftAxis.TickLength = 7
      LeftAxis.TicksInner.Color = 11119017
      LeftAxis.Title.Font.Name = 'Verdana'
      Panning.MouseWheel = pmwNone
      RightAxis.Axis.Color = 4210752
      RightAxis.Grid.Color = 11119017
      RightAxis.LabelsFormat.Font.Name = 'Verdana'
      RightAxis.TicksInner.Color = 11119017
      RightAxis.Title.Font.Name = 'Verdana'
      TopAxis.Automatic = False
      TopAxis.AutomaticMaximum = False
      TopAxis.AutomaticMinimum = False
      TopAxis.Axis.Color = 4210752
      TopAxis.Grid.Color = 11119017
      TopAxis.LabelsFormat.Font.Name = 'Verdana'
      TopAxis.Maximum = 11.000000000000000000
      TopAxis.TicksInner.Color = 11119017
      TopAxis.Title.Font.Name = 'Verdana'
      TopAxis.Items = {
        0F000000010454657874060231340556616C75650500000000000000E0024000
        010454657874060231330556616C75650500000000000000D002400001045465
        7874060231320556616C75650500000000000000C00240000104546578740602
        31320556616C75650500000000000000B0024000010454657874060138055661
        6C75650500000000000000A00240000104546578740601360556616C75650500
        000000000000900240000104546578740601340556616C756505000000000000
        00800240000104546578740601330556616C75650500000000000000E0014000
        0104546578740601320556616C75650500000000000000C00140000104546578
        740603312C350556616C75650500000000000000A00140000104546578740601
        310556616C75650500000000000000800140000104546578740604302C373505
        56616C75650500000000000000C00040000104546578740603302C350556616C
        75650500000000000000800040000104546578740604302C32350556616C7565
        050000000000000080FF3F0001045465787406013000}
      View3D = False
      View3DWalls = False
      BevelOuter = bvNone
      Color = clWhite
      TabOrder = 0
      DefaultCanvas = ''
      ColorPaletteIndex = 13
      object LineSeries1: TLineSeries
        HoverElement = [heCurrent]
        Legend.Visible = False
        HorizAxis = aTopAxis
        SeriesColor = clBlue
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
      object LineSeries2: TLineSeries
        HoverElement = [heCurrent]
        Legend.Visible = False
        HorizAxis = aTopAxis
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
      object LineSeries3: TLineSeries
        HoverElement = [heCurrent]
        Legend.Visible = False
        HorizAxis = aTopAxis
        SeriesColor = clMaroon
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
      object ArrowSeries1: TArrowSeries
        HoverElement = [heCurrent]
        Legend.Visible = False
        HorizAxis = aTopAxis
        Marks.Frame.Visible = False
        Marks.Transparent = True
        SeriesColor = clBlue
        ShowInLegend = False
        ClickableLine = False
        Pointer.InflateMargins = False
        Pointer.Pen.Width = 2
        Pointer.Style = psRectangle
        XValues.DateTime = False
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
        EndXValues.Name = 'EndX'
        EndXValues.Order = loNone
        EndYValues.Name = 'EndY'
        EndYValues.Order = loNone
        StartXValues.DateTime = False
        StartXValues.Name = 'X'
        StartXValues.Order = loAscending
        StartYValues.Name = 'Y'
        StartYValues.Order = loNone
        Data = {0000000000}
        Detail = {0000000000}
      end
      object ArrowSeries2: TArrowSeries
        HoverElement = [heCurrent]
        Legend.Visible = False
        HorizAxis = aTopAxis
        Marks.Frame.Visible = False
        Marks.Transparent = True
        SeriesColor = clRed
        ShowInLegend = False
        ClickableLine = False
        Pointer.InflateMargins = False
        Pointer.Pen.Width = 2
        Pointer.Style = psRectangle
        XValues.DateTime = False
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
        EndXValues.Name = 'EndX'
        EndXValues.Order = loNone
        EndYValues.Name = 'EndY'
        EndYValues.Order = loNone
        StartXValues.DateTime = False
        StartXValues.Name = 'X'
        StartXValues.Order = loAscending
        StartYValues.Name = 'Y'
        StartYValues.Order = loNone
        Data = {0000000000}
        Detail = {0000000000}
      end
      object ArrowSeries3: TArrowSeries
        HoverElement = [heCurrent]
        Legend.Visible = False
        HorizAxis = aTopAxis
        Marks.Frame.Visible = False
        Marks.Transparent = True
        SeriesColor = clMaroon
        ShowInLegend = False
        ClickableLine = False
        Pointer.InflateMargins = False
        Pointer.Pen.Width = 2
        Pointer.Style = psRectangle
        XValues.DateTime = False
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
        EndXValues.Name = 'EndX'
        EndXValues.Order = loNone
        EndYValues.Name = 'EndY'
        EndYValues.Order = loNone
        StartXValues.DateTime = False
        StartXValues.Name = 'X'
        StartXValues.Order = loAscending
        StartYValues.Name = 'Y'
        StartYValues.Order = loNone
        Data = {0000000000}
        Detail = {0000000000}
      end
      object LineSeries4: TLineSeries
        HoverElement = [heCurrent]
        Legend.Visible = False
        HorizAxis = aTopAxis
        SeriesColor = clGreen
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
      object ArrowSeries4: TArrowSeries
        HoverElement = [heCurrent]
        Legend.Visible = False
        HorizAxis = aTopAxis
        Marks.Frame.Visible = False
        Marks.Transparent = True
        SeriesColor = clGreen
        ShowInLegend = False
        ClickableLine = False
        Pointer.InflateMargins = False
        Pointer.Pen.Width = 2
        Pointer.Style = psRectangle
        XValues.DateTime = False
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
        EndXValues.Name = 'EndX'
        EndXValues.Order = loNone
        EndYValues.Name = 'EndY'
        EndYValues.Order = loNone
        StartXValues.DateTime = False
        StartXValues.Name = 'X'
        StartXValues.Order = loAscending
        StartYValues.Name = 'Y'
        StartYValues.Order = loNone
        Data = {0000000000}
      end
    end
  end
  object Panel1: TPanel
    Left = 426
    Top = 422
    Width = 405
    Height = 23
    BevelKind = bkTile
    BevelOuter = bvNone
    Caption = 'WEBER'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWhite
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentBackground = False
    ParentFont = False
    TabOrder = 3
  end
  object WeberPanel5: TPanel
    Left = 746
    Top = 471
    Width = 81
    Height = 41
    BevelKind = bkTile
    BevelOuter = bvNone
    TabOrder = 8
    object WeberImg5: TImage
      Left = 23
      Top = 3
      Width = 32
      Height = 32
    end
  end
  object WeberPanel4: TPanel
    Left = 666
    Top = 471
    Width = 81
    Height = 41
    BevelKind = bkTile
    BevelOuter = bvNone
    TabOrder = 7
    object WeberImg4: TImage
      Left = 23
      Top = 3
      Width = 32
      Height = 32
    end
  end
  object WeberPanel3: TPanel
    Left = 586
    Top = 471
    Width = 81
    Height = 41
    BevelKind = bkTile
    BevelOuter = bvNone
    TabOrder = 6
    object WeberImg3: TImage
      Left = 23
      Top = 3
      Width = 32
      Height = 32
    end
  end
  object WeberPanel2: TPanel
    Left = 506
    Top = 471
    Width = 81
    Height = 41
    BevelKind = bkTile
    BevelOuter = bvNone
    TabOrder = 5
    object WeberImg2: TImage
      Left = 23
      Top = 3
      Width = 32
      Height = 32
    end
  end
  object WeberPanel1: TPanel
    Left = 426
    Top = 471
    Width = 81
    Height = 41
    BevelKind = bkTile
    BevelOuter = bvNone
    TabOrder = 4
    object WeberImg1: TImage
      Left = 23
      Top = 3
      Width = 32
      Height = 32
    end
  end
  object Panel7: TPanel
    Left = 427
    Top = 449
    Width = 81
    Height = 22
    BevelOuter = bvNone
    Caption = '250 hz'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 9
  end
  object Panel8: TPanel
    Left = 507
    Top = 449
    Width = 81
    Height = 22
    BevelOuter = bvNone
    Caption = '500 hz'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 10
  end
  object Panel9: TPanel
    Left = 585
    Top = 449
    Width = 81
    Height = 22
    BevelOuter = bvNone
    Caption = '1000 hz'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 11
  end
  object Panel10: TPanel
    Left = 666
    Top = 449
    Width = 81
    Height = 22
    BevelOuter = bvNone
    Caption = '2000 hz'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 12
  end
  object Panel11: TPanel
    Left = 747
    Top = 449
    Width = 81
    Height = 22
    BevelOuter = bvNone
    Caption = '4000 hz'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 13
  end
  object ImageList1: TImageList
    Height = 32
    Width = 32
    Left = 336
    Top = 528
    Bitmap = {
      494C010103000800040020002000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000800000002000000001002000000000000040
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000C5C5
      C500000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000F0F0F000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000F0F0F000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000C5C5C5000F0F
      0F00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000088888800A7A7A700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000A7A7A700808080000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C5C5C5000F0F0F000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000075757500A0A0A0000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000008888880000000000A7A7A700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000A7A7A700000000008080800000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000C5C5C5000F0F0F00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000001E1E1E00000000006565
      6500F7F7F7000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000888888000000000000000000A7A7A700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000A7A7A700000000000000000080808000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000C5C5C5000F0F0F0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000001E1E1E00000000000000
      000030303000DBDBDB0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000088888800000000000000000000000000A7A7A700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000A7A7A700000000000000000000000000808080000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000C5C5C5000F0F0F000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000001E1E1E00000000000000
      00000000000010101000AFAFAF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00008888880000000000000000000000000000000000A7A7A700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000A7A7A700000000000000000000000000000000008080
      8000000000000000000000000000000000000000000000000000000000000000
      000000000000C5C5C5000F0F0F00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000001E1E1E00000000000000
      000000000000000000000101010071717100FBFBFB0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000007F7F
      7F00000000000000000000000000000000000000000016161600222222002222
      2200222222002222220022222200222222002222220022222200222222002222
      2200222222002222220016161600000000000000000000000000000000000000
      00007F7F7F000000000000000000000000000000000000000000000000000000
      0000C5C5C5000F0F0F0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000029292900EBEBEB000000000000000000000000000000000000000000F0F0
      F000EEEEEE00EEEEEE00EEEEEE00EEEEEE00EEEEEE00EEEEEE00EEEEEE00EEEE
      EE00EEEEEE00EEEEEE00EEEEEE00EEEEEE00EEEEEE001C1C1C00000000000000
      0000000000000000000000000000000000003D3D3D00E4E4E400000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000888888000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000808080000000000000000000000000000000000000000000C5C5
      C5000F0F0F000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000A9A9A90000000000000000000000000000000000A0A0A0000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000015151500BCBCBC000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000088888800000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000080808000000000000000000000000000C5C5C5000F0F
      0F00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000A5A5A50000000000000000000000000000000000878787000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000030303008282
      8200FDFDFD000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008888880000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000008080800000000000C5C5C5000F0F0F000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000A5A5A50000000000000000000000000000000000878787000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000048484800FAFAFA0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007F7F7F0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000007777770000000000C5C5C5000F0F0F000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000A5A5A50000000000000000000000000000000000878787000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00001B1B1B00EFEFEF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000007F7F7F00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000077777700000000000000000000000000C5C5C5000F0F
      0F00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000A5A5A50000000000000000000000000000000000878787000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000004545
      4500EAEAEA000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000007F7F7F000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000777777000000000000000000000000000000000000000000C5C5
      C5000F0F0F000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000A9A9A900000000000000000000000000000000008D8D8D000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000020202007D7D7D00FCFC
      FC00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000007F7F
      7F00000000000000000000000000000000000000000016161600222222002222
      2200222222002222220022222200222222002222220022222200222222002222
      2200222222002222220016161600000000000000000000000000000000000000
      00007F7F7F000000000000000000000000000000000000000000000000000000
      0000C5C5C5000F0F0F0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000028282800EAEAEA0000000000000000000000000000000000F2F2F200ADAD
      AD00AAAAAA00AAAAAA00AAAAAA00AAAAAA00AAAAAA00AAAAAA00AAAAAA00AAAA
      AA00AAAAAA00AAAAAA00AAAAAA00AAAAAA00AAAAAA0014141400000000000000
      00000000000000000000000000000000000013131300B9B9B900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007F7F7F0000000000000000000000000000000000A7A7A700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000A7A7A700000000000000000000000000000000007777
      7700000000000000000000000000000000000000000000000000000000000000
      000000000000C5C5C5000F0F0F00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000001E1E1E00000000000000
      000000000000000000000000000038383800E1E1E10000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000007F7F7F00000000000000000000000000A7A7A700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000A7A7A700000000000000000000000000777777000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000C5C5C5000F0F0F000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000001E1E1E00000000000000
      000000000000000000006E6E6E00FAFAFA000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000007F7F7F000000000000000000A7A7A700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000A7A7A700000000000000000077777700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000C5C5C5000F0F0F0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000001E1E1E00000000000000
      00000E0E0E00AAAAAA0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000007F7F7F0000000000A7A7A700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000A7A7A700000000007777770000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000C5C5C5000F0F0F00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000001E1E1E00000000002C2C
      2C00DADADA000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007F7F7F00A7A7A700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000A7A7A700777777000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C5C5C5000F0F0F000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000003A3A3A0061616100F5F5
      F500000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000F0F0F000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000F0F0F000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000C5C5C5000F0F
      0F00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000C5C5
      C500000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000080000000200000000100010000000000000200000000000000000000
      000000000000000000000000FFFFFF00FFFFFFFFFFFFFFFFFFFFFFFF00000000
      FFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFFFFFFFFFF00000000
      FFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFFFFFFFFFF00000000
      FFFFFFFFFFEFFFFFFFFFFFFF00000000FFBFFDFFFFCFFFFFFFFFFFFF00000000
      FF3FFCFFFF8FFFFFFFFF9FFF00000000FE3FFC7FFF0FFFFFFFFF87FF00000000
      FC3FFC3FFE0FFFFFFFFF83FF00000000F83FFC1FFC0FFFFFFFFF81FF00000000
      F03FFC0FF80FFFFFFFFF807F00000000E0000007F0000003E000003F00000000
      C0000003E0000003C000001F0000000080000001C0000003C000000700000000
      0000000080000003C0000003000000000000000080000003C000000300000000
      80000001C0000003C000000700000000C0000003E0000003C000000F00000000
      E0000007F0000003C000003F00000000F03FFC0FF80FFFFFFFFF807F00000000
      F83FFC1FFC0FFFFFFFFF80FF00000000FC3FFC3FFE0FFFFFFFFF83FF00000000
      FE3FFC7FFF0FFFFFFFFF87FF00000000FF3FFCFFFF8FFFFFFFFF8FFF00000000
      FFBFFDFFFFCFFFFFFFFFFFFF00000000FFFFFFFFFFEFFFFFFFFFFFFF00000000
      FFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFFFFFFFFFF00000000
      FFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFFFFFFFFFF00000000
      FFFFFFFFFFFFFFFFFFFFFFFF0000000000000000000000000000000000000000
      000000000000}
  end
end
