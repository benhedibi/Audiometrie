object GainpImpFrm: TGainpImpFrm
  Left = 0
  Top = 0
  Width = 1023
  Height = 717
  VertScrollBar.Position = 432
  AutoScroll = True
  Caption = 'GainpImpFrm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Scaled = False
  PixelsPerInch = 96
  TextHeight = 13
  object QuickRep1: TQuickRep
    Left = 0
    Top = -432
    Width = 794
    Height = 1123
    ShowingPreview = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Calibri'
    Font.Style = []
    Functions.Strings = (
      'PAGENUMBER'
      'COLUMNNUMBER'
      'REPORTTITLE'
      'QRSTRINGSBAND1')
    Functions.DATA = (
      '0'
      '0'
      #39#39
      #39#39)
    Options = [FirstPageHeader, LastPageFooter]
    Page.Columns = 1
    Page.Orientation = poPortrait
    Page.PaperSize = A4
    Page.Continuous = False
    Page.Values = (
      100.000000000000000000
      2970.000000000000000000
      100.000000000000000000
      2100.000000000000000000
      100.000000000000000000
      100.000000000000000000
      0.000000000000000000)
    PrinterSettings.Copies = 1
    PrinterSettings.OutputBin = Auto
    PrinterSettings.Duplex = False
    PrinterSettings.FirstPage = 0
    PrinterSettings.LastPage = 0
    PrinterSettings.UseStandardprinter = False
    PrinterSettings.UseCustomBinCode = False
    PrinterSettings.CustomBinCode = 0
    PrinterSettings.ExtendedDuplex = 0
    PrinterSettings.UseCustomPaperCode = False
    PrinterSettings.CustomPaperCode = 0
    PrinterSettings.PrintMetaFile = False
    PrinterSettings.MemoryLimit = 1000000
    PrinterSettings.PrintQuality = 0
    PrinterSettings.Collate = 0
    PrinterSettings.ColorOption = 0
    PrintIfEmpty = True
    SnapToGrid = True
    Units = MM
    Zoom = 100
    PrevFormStyle = fsNormal
    PreviewInitialState = wsMaximized
    PreviewWidth = 500
    PreviewHeight = 500
    PrevShowThumbs = False
    PrevShowSearch = False
    PrevInitialZoom = qrZoomToFit
    PreviewDefaultSaveType = stPDF
    PreviewLeft = 0
    PreviewTop = 0
    object TitleBand1: TQRBand
      Left = 38
      Top = 38
      Width = 718
      Height = 94
      AlignToBottom = False
      TransparentBand = False
      ForceNewColumn = False
      ForceNewPage = False
      Size.Values = (
        248.708333333333300000
        1899.708333333333000000)
      PreCaluculateBandHeight = False
      KeepOnOnePage = False
      BandType = rbTitle
      object QRLabel1: TQRLabel
        Left = 48
        Top = 8
        Width = 126
        Height = 27
        Size.Values = (
          71.437500000000000000
          127.000000000000000000
          21.166666666666670000
          333.375000000000000000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = 'ALI ZEKRI (Lotfi)'
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'Calibri'
        Font.Style = [fsBold]
        ParentFont = False
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 14
      end
      object QRLabel2: TQRLabel
        Left = 16
        Top = 33
        Width = 195
        Height = 20
        Size.Values = (
          52.916666666666670000
          42.333333333333330000
          87.312500000000000000
          515.937500000000000000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = 'Analyse & Correction Auditive'
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Calibri'
        Font.Style = []
        ParentFont = False
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 12
      end
      object QRLabel3: TQRLabel
        Left = 544
        Top = 8
        Width = 167
        Height = 20
        Size.Values = (
          52.916666666666670000
          1439.333333333333000000
          21.166666666666670000
          441.854166666666700000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = '22 , Rue El Jazira 1000 Tunis'
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Calibri'
        Font.Style = []
        ParentFont = False
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object QRLabel4: TQRLabel
        Left = 514
        Top = 30
        Width = 197
        Height = 20
        Size.Values = (
          52.916666666666670000
          1359.958333333333000000
          79.375000000000000000
          521.229166666666700000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = 'T'#233'l : 71 324 934 / Fax : 71 325 994'
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Calibri'
        Font.Style = []
        ParentFont = False
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object QRLabel5: TQRLabel
        Left = 514
        Top = 52
        Width = 197
        Height = 20
        Size.Values = (
          52.916666666666670000
          1359.958333333333000000
          137.583333333333300000
          521.229166666666700000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = 'E-mail : lotfizekri35@gmail.com'
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Calibri'
        Font.Style = []
        ParentFont = False
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object QRShape1: TQRShape
        Left = 0
        Top = 80
        Width = 718
        Height = 25
        Size.Values = (
          66.145833333333330000
          0.000000000000000000
          211.666666666666700000
          1899.708333333333000000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Shape = qrsHorLine
        VertAdjust = 0
      end
    end
    object PageFooterBand1: TQRBand
      Left = 38
      Top = 992
      Width = 718
      Height = 90
      AlignToBottom = False
      TransparentBand = False
      ForceNewColumn = False
      ForceNewPage = False
      Size.Values = (
        238.125000000000000000
        1899.708333333333000000)
      PreCaluculateBandHeight = False
      KeepOnOnePage = False
      BandType = rbPageFooter
      object QRLabel11: TQRLabel
        Left = 16
        Top = 8
        Width = 90
        Height = 20
        Size.Values = (
          52.916666666666670000
          42.333333333333330000
          21.166666666666670000
          238.125000000000000000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = 'Observations :'
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Calibri'
        Font.Style = [fsUnderline]
        ParentFont = False
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object QRMemo1: TQRMemo
        Left = 16
        Top = 34
        Width = 66
        Height = 20
        Size.Values = (
          52.916666666666670000
          42.333333333333330000
          89.958333333333330000
          174.625000000000000000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Color = clWhite
        Transparent = False
        FullJustify = False
        MaxBreakChars = 0
        FontSize = 11
      end
    end
    object SummaryBand1: TQRBand
      Left = 38
      Top = 318
      Width = 718
      Height = 672
      AlignToBottom = False
      TransparentBand = False
      ForceNewColumn = False
      ForceNewPage = False
      Size.Values = (
        1778.000000000000000000
        1899.708333333333000000)
      PreCaluculateBandHeight = False
      KeepOnOnePage = False
      BandType = rbSummary
      object QRLabel12: TQRLabel
        Left = 279
        Top = 6
        Width = 159
        Height = 30
        Size.Values = (
          79.375000000000000000
          738.187500000000000000
          15.875000000000000000
          420.687500000000000000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = 'GAIN PROTHETIQUE'
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'Calibri'
        Font.Style = [fsBold]
        ParentFont = False
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 14
      end
      object GainpImg: TQRImage
        AlignWithMargins = True
        Left = 75
        Top = 188
        Width = 568
        Height = 313
        Size.Values = (
          828.145833333333300000
          198.437500000000000000
          497.416666666666700000
          1502.833333333333000000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
      end
      object OdDate1: TQRLabel
        Left = 454
        Top = 506
        Width = 15
        Height = 19
        Size.Values = (
          50.270833333333330000
          1201.208333333333000000
          1338.791666666667000000
          39.687500000000000000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = 'S.A'
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Calibri'
        Font.Style = []
        Font.Quality = fqClearType
        ParentFont = False
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 8
      end
      object OdShape1: TQRShape
        Left = 434
        Top = 507
        Width = 10
        Height = 10
        Size.Values = (
          26.458333333333330000
          1148.291666666667000000
          1341.437500000000000000
          26.458333333333330000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Brush.Color = clHotLight
        Pen.Color = clHotLight
        Shape = qrsRectangle
        VertAdjust = 0
      end
      object OdShape2: TQRShape
        Left = 511
        Top = 507
        Width = 10
        Height = 10
        Size.Values = (
          26.458333333333330000
          1352.020833333333000000
          1341.437500000000000000
          26.458333333333330000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Brush.Color = clRed
        Pen.Color = clRed
        Shape = qrsRectangle
        VertAdjust = 0
      end
      object OdDate2: TQRLabel
        Left = 530
        Top = 506
        Width = 15
        Height = 19
        Size.Values = (
          50.270833333333330000
          1402.291666666667000000
          1338.791666666667000000
          39.687500000000000000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = 'S.P'
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Calibri'
        Font.Style = []
        ParentFont = False
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 8
      end
      object OgDate1: TQRLabel
        Left = 604
        Top = 506
        Width = 27
        Height = 19
        Size.Values = (
          50.270833333333330000
          1598.083333333333000000
          1338.791666666667000000
          71.437500000000000000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = 'M.C.L'
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Calibri'
        Font.Style = []
        Font.Quality = fqClearType
        ParentFont = False
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 8
      end
      object OgShape1: TQRShape
        Left = 586
        Top = 507
        Width = 10
        Height = 10
        Size.Values = (
          26.458333333333330000
          1549.702380952381000000
          1341.815476190476000000
          26.458333333333330000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Brush.Color = clMaroon
        Pen.Color = clMaroon
        Shape = qrsRectangle
        VertAdjust = 0
      end
      object QRLabel13: TQRLabel
        Left = 107
        Top = 73
        Width = 67
        Height = 19
        Size.Values = (
          50.270833333333330000
          283.104166666666700000
          193.145833333333300000
          177.270833333333300000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = 'Oreille(s) :'
        Color = clWhite
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object QRLabel14: TQRLabel
        Left = 123
        Top = 98
        Width = 51
        Height = 19
        Size.Values = (
          50.270833333333330000
          325.437500000000000000
          259.291666666666700000
          134.937500000000000000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = 'Nature :'
        Color = clWhite
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object QRLabel15: TQRLabel
        Left = 77
        Top = 123
        Width = 97
        Height = 19
        Size.Values = (
          50.270833333333330000
          203.729166666666700000
          325.437500000000000000
          256.645833333333300000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = 'Type Proth'#232'se :'
        Color = clWhite
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object QRLabel16: TQRLabel
        Left = 102
        Top = 148
        Width = 72
        Height = 19
        Size.Values = (
          50.270833333333330000
          269.875000000000000000
          391.583333333333300000
          190.500000000000000000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = 'R'#233'f'#233'rence :'
        Color = clWhite
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object QRLabel17: TQRLabel
        Left = 98
        Top = 528
        Width = 96
        Height = 19
        Size.Values = (
          50.270833333333330000
          259.291666666666700000
          1397.000000000000000000
          254.000000000000000000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = 'Seuil Audition :'
        Color = clWhite
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object QRLabel18: TQRLabel
        Left = 77
        Top = 553
        Width = 117
        Height = 19
        Size.Values = (
          50.270833333333330000
          203.729166666666700000
          1463.145833333333000000
          309.562500000000000000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = 'Seuil Proth'#233'tique :'
        Color = clWhite
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object QRLabel19: TQRLabel
        Left = 80
        Top = 578
        Width = 114
        Height = 19
        Size.Values = (
          50.270833333333330000
          211.666666666666700000
          1529.291666666667000000
          301.625000000000000000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = 'Gain Proth'#233'tique :'
        Color = clWhite
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object QRLabel20: TQRLabel
        Left = 152
        Top = 628
        Width = 42
        Height = 19
        Size.Values = (
          50.270833333333330000
          402.166666666666700000
          1661.583333333333000000
          111.125000000000000000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = 'M.C.L :'
        Color = clWhite
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object QRLabel21: TQRLabel
        Left = 115
        Top = 603
        Width = 79
        Height = 19
        Size.Values = (
          50.270833333333330000
          304.270833333333300000
          1595.437500000000000000
          209.020833333333300000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = 'Dynamique :'
        Color = clWhite
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object SeuilAuditionLbl: TQRLabel
        Left = 200
        Top = 528
        Width = 1
        Height = 19
        Size.Values = (
          50.270833333333330000
          529.166666666666700000
          1397.000000000000000000
          2.645833333333333000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = ''
        Color = clWhite
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object SeuilProtLbl: TQRLabel
        Left = 200
        Top = 553
        Width = 1
        Height = 19
        Size.Values = (
          50.270833333333330000
          529.166666666666700000
          1463.145833333333000000
          2.645833333333333000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = ''
        Color = clWhite
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object GpLbl: TQRLabel
        Left = 200
        Top = 578
        Width = 1
        Height = 19
        Size.Values = (
          50.270833333333330000
          529.166666666666700000
          1529.291666666667000000
          2.645833333333333000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = ''
        Color = clWhite
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object DynLbl: TQRLabel
        Left = 200
        Top = 603
        Width = 1
        Height = 19
        Size.Values = (
          50.270833333333330000
          529.166666666666700000
          1595.437500000000000000
          2.645833333333333000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = ''
        Color = clWhite
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object MclLbl: TQRLabel
        Left = 200
        Top = 628
        Width = 1
        Height = 19
        Size.Values = (
          50.270833333333330000
          529.166666666666700000
          1661.583333333333000000
          2.645833333333333000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = ''
        Color = clWhite
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object OreilleLbl: TQRLabel
        Left = 180
        Top = 73
        Width = 1
        Height = 19
        Size.Values = (
          50.270833333333330000
          476.250000000000000000
          193.145833333333300000
          2.645833333333333000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = ''
        Color = clWhite
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object NatureLbl: TQRLabel
        Left = 180
        Top = 98
        Width = 1
        Height = 19
        Size.Values = (
          50.270833333333330000
          476.250000000000000000
          259.291666666666700000
          2.645833333333333000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = ''
        Color = clWhite
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object ProtLbl: TQRLabel
        Left = 180
        Top = 123
        Width = 1
        Height = 19
        Size.Values = (
          50.270833333333330000
          476.250000000000000000
          325.437500000000000000
          2.645833333333333000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = ''
        Color = clWhite
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object RefLbl: TQRLabel
        Left = 180
        Top = 148
        Width = 1
        Height = 19
        Size.Values = (
          50.270833333333330000
          476.250000000000000000
          391.583333333333300000
          2.645833333333333000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = ''
        Color = clWhite
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object QRLabel22: TQRLabel
        Left = 351
        Top = 168
        Width = 17
        Height = 19
        Size.Values = (
          50.270833333333330000
          928.687500000000000000
          444.500000000000000000
          44.979166666666670000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = 'Khz'
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Calibri'
        Font.Style = []
        ParentFont = False
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 8
      end
      object QRLabel23: TQRLabel
        Left = 56
        Top = 328
        Width = 13
        Height = 19
        Size.Values = (
          50.270833333333330000
          148.166666666666700000
          867.833333333333300000
          34.395833333333330000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = 'db'
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Calibri'
        Font.Style = []
        ParentFont = False
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 8
      end
    end
    object QRBand1: TQRBand
      Left = 38
      Top = 132
      Width = 718
      Height = 186
      AlignToBottom = False
      TransparentBand = False
      ForceNewColumn = False
      ForceNewPage = False
      Size.Values = (
        492.125000000000000000
        1899.708333333333000000)
      PreCaluculateBandHeight = False
      KeepOnOnePage = False
      BandType = rbDetail
      object QRLabel7: TQRLabel
        Left = 15
        Top = 50
        Width = 103
        Height = 20
        Size.Values = (
          52.916666666666670000
          39.687500000000000000
          132.291666666666700000
          272.520833333333300000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = 'Nom & Pr'#233'nom :'
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Calibri'
        Font.Style = []
        ParentFont = False
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object QRLabel6: TQRLabel
        Left = 30
        Top = 76
        Width = 88
        Height = 20
        Size.Values = (
          52.916666666666670000
          79.375000000000000000
          201.083333333333300000
          232.833333333333300000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = 'Code Patient :'
        Color = clWhite
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object QRLabel8: TQRLabel
        Left = 60
        Top = 102
        Width = 58
        Height = 20
        Size.Values = (
          52.916666666666670000
          158.750000000000000000
          269.875000000000000000
          153.458333333333300000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = 'Adresse :'
        Color = clWhite
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object QRLabel9: TQRLabel
        Left = 56
        Top = 128
        Width = 62
        Height = 20
        Size.Values = (
          52.916666666666670000
          148.166666666666700000
          338.666666666666700000
          164.041666666666700000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = 'M'#233'decin :'
        Color = clWhite
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object QRLabel10: TQRLabel
        Left = 546
        Top = 12
        Width = 60
        Height = 20
        Size.Values = (
          52.916666666666670000
          1444.625000000000000000
          31.750000000000000000
          158.750000000000000000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = 'Tunis, le :'
        Color = clWhite
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object DateLbl: TQRLabel
        Left = 612
        Top = 12
        Width = 1
        Height = 20
        Size.Values = (
          52.916666666666670000
          1619.250000000000000000
          31.750000000000000000
          2.645833333333333000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = ''
        Color = clWhite
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object NomLbl: TQRLabel
        Left = 125
        Top = 50
        Width = 1
        Height = 20
        Size.Values = (
          52.916666666666670000
          330.729166666666700000
          132.291666666666700000
          2.645833333333333000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = ''
        Color = clWhite
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object CodepLbl: TQRLabel
        Left = 125
        Top = 76
        Width = 1
        Height = 20
        Size.Values = (
          52.916666666666670000
          330.729166666666700000
          201.083333333333300000
          2.645833333333333000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = ''
        Color = clWhite
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object AdressLbl: TQRLabel
        Left = 125
        Top = 102
        Width = 1
        Height = 20
        Size.Values = (
          52.916666666666670000
          330.729166666666700000
          269.875000000000000000
          2.645833333333333000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = ''
        Color = clWhite
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object MedLbl: TQRLabel
        Left = 125
        Top = 128
        Width = 1
        Height = 20
        Size.Values = (
          52.916666666666670000
          330.729166666666700000
          338.666666666666700000
          2.645833333333333000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Alignment = taLeftJustify
        AlignToBand = False
        Caption = ''
        Color = clWhite
        Transparent = False
        ExportAs = exptText
        WrapStyle = BreakOnSpaces
        VerticalAlignment = tlTop
        FontSize = 11
      end
      object QRShape2: TQRShape
        Left = 0
        Top = 176
        Width = 718
        Height = 16
        Size.Values = (
          42.333333333333330000
          0.000000000000000000
          465.666666666666700000
          1899.708333333333000000)
        XLColumn = 0
        XLNumFormat = nfGeneral
        ActiveInPreview = False
        Shape = qrsHorLine
        VertAdjust = 0
      end
    end
  end
end
