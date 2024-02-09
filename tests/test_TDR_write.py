import pyDICOS
from pyDICOS import (
    CT,
    TDR,
    Array1DPoint3Dfloat,
    Bitmap,
    CustomArray1DDcsLongString,
    DcsDate,
    DcsDateTime,
    DcsGUID,
    DcsLongString,
    DcsLongText,
    DcsShortString,
    DcsShortText,
    DcsTime,
    DcsUniqueIdentifier,
    ErrorLog,
    Filename,
    Folder,
    GeneralSeriesModule,
    Point3Dfloat,
    Point3DS_UINT16,
    Section,
    Vector3Dfloat,
    Volume,
)


def test_no_threat_tdr(session_cleanup):
    TDRInstanceNumber = 1234
    # The OBJECT_OF_INSPECTION_TYPE enumeration is situated in the binding code of the CT Module.
    # The TDR_TYPE enumeration is situated in the binding code of the TDR Module.
    tdr = TDR(
        CT.OBJECT_OF_INSPECTION_TYPE.enumTypeBaggage,
        TDR.TDR_TYPE.enumMachine,
        TDRInstanceNumber,
    )

    TDRCreationStartDate = DcsDate.Today()
    TDRCreationStartTime = DcsTime.Now()
    tdr.SetContentDateAndTime(TDRCreationStartDate, TDRCreationStartTime)

    atrManufacturer = DcsLongString("Alchemy")
    atrVersion = DcsLongString("0.999")

    # DcsLongString in CustomArray1DDcsLongString means that the type of the components of CustomArray1D is DcsLongString"
    # the supported types of CustomArray1D us : DcsLongString
    ATR_Parameters = CustomArray1DDcsLongString(2)
    item1 = DcsLongString("-random=true")
    item2 = DcsLongString("-magic=true")
    ATR_Parameters.SetBuffer(0, item1)
    ATR_Parameters.SetBuffer(1, item2)
    tdr.SetTDRTypeATR(atrManufacturer, atrVersion, ATR_Parameters)

    tdr.SetImageScaleRepresentation(10.0)

    # The ALARM_DECISION enumeration is situated in the binding code of the TDR Module.
    tdr.SetAlarmDecision(TDR.ALARM_DECISION.enumClear)
    alarmDecisionDate = DcsDate(1944, 6, 6)
    alarmDecisionTime = DcsTime(6, 30, 0, 0)
    tdr.SetAlarmDecisionDateTime(alarmDecisionDate, alarmDecisionTime)

    # The ABORT_FLAG enumeration is situated in the binding code of the TDR Module.
    tdr.SetAbortFlag(TDR.ABORT_FLAG.enumSuccess)
    uidSopInstanceCT = DcsUniqueIdentifier(DcsGUID.GenerateAsDecimalString())
    uidSopClassCT = DcsUniqueIdentifier(pyDICOS.GetCT())
    tdr.AddReferencedSopInstance(uidSopInstanceCT, uidSopClassCT)

    errorlog = ErrorLog()
    tdrFolder = Folder("TDRFiles")
    tdrFilename = Filename(tdrFolder, "SimpleBaggageNoThreatTDR.dcs")
    session_cleanup.append("TDRFiles")

    assert tdr.Write(
        tdrFilename, errorlog
    ), f"Simple TDR Template Example unable to write DICOS File : {tdrFilename}\n{errorlog.GetErrorLog().Get()}"

    tdrRead = TDR()
    errorlog = ErrorLog()

    assert tdrRead.Read(
        tdrFilename, errorlog, None
    ), f"Unable to read TDR file {tdrFilename}\n{errorlog.GetErrorLog().Get()}"

    assert (
        tdrRead == tdr
    ), f"TDR file loaded from {tdrFilename} does not match original.\n{errorlog.GetErrorLog().Get()}"


def test_baggage_tdr(session_cleanup):
    TDRInstanceNumber = 1234
    # The OBJECT_OF_INSPECTION_TYPE enumeration is situated in the binding code of the CT Module.
    # The TDR_TYPE enumeration is situated in the binding code of the TDR Module.
    tdr = TDR(
        CT.OBJECT_OF_INSPECTION_TYPE.enumTypeBaggage,
        TDR.TDR_TYPE.enumMachine,
        TDRInstanceNumber,
    )

    TDRCreationStartDate = DcsDate.Today()
    TDRCreationStartTime = DcsTime.Now()
    tdr.SetContentDateAndTime(TDRCreationStartDate, TDRCreationStartTime)

    atrManufacturer = DcsLongString("Alchemy")
    atrVersion = DcsLongString("0.999")

    # DcsLongString in CustomArray1DDcsLongString means that the type of the components of CustomArray1D is DcsLongString"
    # the supported types of CustomArray1D us : DcsLongString
    ATR_Parameters = CustomArray1DDcsLongString(2)
    item1 = DcsLongString("-random=true")
    item2 = DcsLongString("-magic=true")
    ATR_Parameters.SetBuffer(0, item1)
    ATR_Parameters.SetBuffer(1, item2)
    tdr.SetTDRTypeATR(atrManufacturer, atrVersion, ATR_Parameters)

    tdr.SetImageScaleRepresentation(10.0)

    # The ALARM_DECISION enumeration is situated in the binding code of the TDR Module.
    tdr.SetAlarmDecision(TDR.ALARM_DECISION.enumClear)
    alarmDecisionDate = DcsDate(1944, 6, 6)
    alarmDecisionTime = DcsTime(6, 30, 0, 0)
    tdr.SetAlarmDecisionDateTime(alarmDecisionDate, alarmDecisionTime)

    # The ABORT_FLAG enumeration is situated in the binding code of the TDR Module.
    tdr.SetAbortFlag(TDR.ABORT_FLAG.enumSuccess)

    tdr.SetTotalProcessingTimeInMS(500.0)

    PTOIdentifier0 = 9001
    # The ThreatType enumeration is situated in the binding code of the TDR Module.
    tdr.AddPotentialThreatObject(PTOIdentifier0, TDR.ThreatType.enumThreatTypeBaggage)

    threatDescription = DcsLongText("Flammable Liquid")
    # The ASSESSMENT_FLAG enumeration is situated in the binding code of the TDR Module.
    # The THREAT_CATEGORY enumeration is situated in the binding code of the TDR Module.
    # The ABILITY_ASSESSMENT enumeration is situated in the binding code of the TDR Module.
    tdr.AddPTOAssessment(
        PTOIdentifier0,
        TDR.ASSESSMENT_FLAG.enumThreat,
        TDR.THREAT_CATEGORY.enumProhibitedItem,
        TDR.ABILITY_ASSESSMENT.enumNoInterference,
        threatDescription,
        -1.0,
    )

    tdr.SetBaggagePTODetails(PTOIdentifier0, 50.0, 7000.0, 0)

    ptoDims = Point3Dfloat(50, 50, 100)
    ptoMask = Bitmap(50, 50, 100)

    for d in range(int(ptoDims.z)):
        if d > 30 and d < 70:
            continue
        for h in range(int(ptoDims.y)):
            if h > 10 and d < 40:
                continue
            for w in range(int(ptoDims.x)):
                index = w + h * int(ptoDims.x) + d * int(ptoDims.x * ptoDims.y)
                value = None
                if w > 10 and w < 20:
                    value = False
                else:
                    value = True
                ptoMask.SetBit(w, h, d, value)
                assert value == ptoMask.GetBit(
                    index
                ), f"Failed to validate threat bitmask({w}, {h}, {d})"

    tdr.SetThreatRegionOfInterest(
        PTOIdentifier0, Point3Dfloat(12, 23, 45), ptoDims, ptoMask, 0
    )

    dateTime = DcsDateTime()
    dateTime.SetNow()
    tdr.SetPTOProcessingTime(PTOIdentifier0, dateTime, dateTime, 0.0)

    CTReferenceUID = DcsUniqueIdentifier("1235.23456.568678.34546")
    uidSopClassCT = DcsUniqueIdentifier(pyDICOS.GetCT())
    tdr.AddReferencedInstance(PTOIdentifier0, uidSopClassCT, CTReferenceUID, 0)

    errorlog = ErrorLog()
    tdrFolder = Folder("TDRFiles")
    tdrFilename = Filename(tdrFolder, "SimpleBaggageTDR.dcs")
    session_cleanup.append("TDRFiles")

    assert tdr.Write(
        tdrFilename, errorlog
    ), f"Simple TDR Template Example unable to write DICOS File : {tdrFilename}\n{errorlog.GetErrorLog().Get()}"

    tdrRead = TDR()
    errorlog = ErrorLog()

    assert tdrRead.Read(
        tdrFilename, errorlog, None
    ), f"Unable to read TDR file {tdrFilename}\n{errorlog.GetErrorLog().Get()}"

    assert (
        tdrRead == tdr
    ), f"TDR file loaded from {tdrFilename} does not match original.\n{errorlog.GetErrorLog().Get()}"


def test_multiple_ptos_tdr(session_cleanup):
    TDRInstanceNumber = 1234
    # The OBJECT_OF_INSPECTION_TYPE enumeration is situated in the binding code of the CT Module.
    # The TDR_TYPE enumeration is situated in the binding code of the TDR Module.
    tdr = TDR(
        CT.OBJECT_OF_INSPECTION_TYPE.enumTypeBaggage,
        TDR.TDR_TYPE.enumMachine,
        TDRInstanceNumber,
    )

    OOIIdentifier = DcsLongString("12345-35345324-6326342-345")
    tdr.SetOOIID(OOIIdentifier)
    tdr.SetOOIIDAssigningAuthority(DcsLongString("TSA"))
    # The OBJECT_OF_INSPECTION_ID_TYPE enumeration is situated in the binding code of the TDR Module.
    tdr.SetOOIIDType(TDR.OBJECT_OF_INSPECTION_ID_TYPE.enumRFID)

    TDRCreationStartDate = DcsDate.Today()
    TDRCreationStartTime = DcsTime.Now()
    tdr.SetContentDateAndTime(TDRCreationStartDate, TDRCreationStartTime)

    atrManufacturer = DcsLongString("Alchemy")
    atrVersion = DcsLongString("0.999")

    # DcsLongString in CustomArray1DDcsLongString means that the type of the components of CustomArray1D is DcsLongString"
    # the supported types of CustomArray1D us : DcsLongString
    ATR_Parameters = CustomArray1DDcsLongString(2)
    item1 = DcsLongString("-random=true")
    item2 = DcsLongString("-magic=true")
    ATR_Parameters.SetBuffer(0, item1)
    ATR_Parameters.SetBuffer(1, item2)
    tdr.SetTDRTypeATR(atrManufacturer, atrVersion, ATR_Parameters)

    tdr.SetImageScaleRepresentation(10.0)

    tdr.SetAlarmDecision(TDR.ALARM_DECISION.enumAlarm)
    alarmDecisionDate = DcsDate(1944, 6, 6)
    alarmDecisionTime = DcsTime(6, 30, 0, 0)
    tdr.SetAlarmDecisionDateTime(alarmDecisionDate, alarmDecisionTime)

    # The ABORT_FLAG enumeration is situated in the binding code of the TDR Module.
    tdr.SetAbortFlag(TDR.ABORT_FLAG.enumSuccess)

    tdr.SetTotalProcessingTimeInMS(500.0)

    PTOIdentifier0 = 9001
    tdr.AddPotentialThreatObject(PTOIdentifier0, TDR.ThreatType.enumThreatTypeBaggage)

    threatDescription = DcsLongText("Flammable Liquid")
    # The ASSESSMENT_FLAG enumeration is situated in the binding code of the TDR Module.
    # The THREAT_CATEGORY enumeration is situated in the binding code of the TDR Module.
    # The ABILITY_ASSESSMENT enumeration is situated in the binding code of the TDR Module.
    tdr.AddPTOAssessment(
        PTOIdentifier0,
        TDR.ASSESSMENT_FLAG.enumHighThreat,
        TDR.THREAT_CATEGORY.enumProhibitedItem,
        TDR.ABILITY_ASSESSMENT.enumNoInterference,
        threatDescription,
        -1.0,
    )

    tdr.SetBaggagePTODetails(PTOIdentifier0, 50.0, 7000.0, 0)

    tdr.SetThreatRegionOfInterest(
        PTOIdentifier0, Point3Dfloat(12, 23, 45), Point3Dfloat(50, 50, 100), Bitmap(), 0
    )

    dateTime = DcsDateTime()
    dateTime.SetNow()
    tdr.SetPTOProcessingTime(PTOIdentifier0, dateTime, dateTime, 0.0)

    PTOIdentifier1 = 2002
    # The ThreatType enumeration is situated in the binding code of the TDR Module.
    tdr.AddPotentialThreatObject(PTOIdentifier1, TDR.ThreatType.enumThreatTypeBaggage)

    # The ASSESSMENT_FLAG enumeration is situated in the binding code of the TDR Module.
    # The THREAT_CATEGORY enumeration is situated in the binding code of the TDR Module.
    # The ABILITY_ASSESSMENT enumeration is situated in the binding code of the TDR Module.
    tdr.AddPTOAssessment(
        PTOIdentifier1,
        TDR.ASSESSMENT_FLAG.enumNoThreat,
        TDR.THREAT_CATEGORY.enumAnomaly,
        TDR.ABILITY_ASSESSMENT.enumNoInterference,
        DcsLongText(""),
        float(-10),
    )

    tdr.SetBaggagePTODetails(PTOIdentifier1, 100.0, 40.0, 0)

    tdr.SetThreatRegionOfInterest(
        PTOIdentifier1, Point3Dfloat(1, 23, 95), Point3Dfloat(22, 33, 444), Bitmap(), 0
    )

    tdr.SetPTOProcessingTime(PTOIdentifier1, dateTime, dateTime, 0.0)

    # float in Array1DPoint3D means that the type of the components of Array1DPoint3D is float
    # the supported types of Array1DPoint3D are : S_UINT8, S_INT8, S_UINT16, S_INT16, float
    # Array1DPoint3D means that the type of the components of Array1D is Point3D
    bp = Array1DPoint3Dfloat()
    bp.SetSize(3, False)

    bp[0] = Point3Dfloat(1, 2, 3)
    bp[1] = Point3Dfloat(3, 4, 5)
    bp[2] = Point3Dfloat(6, 7, 8)
    tdr.SetThreatBoundingPolygon(PTOIdentifier1, bp, 0)

    CTReferenceUID = DcsUniqueIdentifier("1235.23456.568678.34546")
    uidSopClassCT = DcsUniqueIdentifier(pyDICOS.GetCT())
    tdr.AddReferencedInstance(PTOIdentifier0, uidSopClassCT, CTReferenceUID, 0)
    tdr.AddReferencedInstance(PTOIdentifier1, uidSopClassCT, CTReferenceUID, 0)

    errorlog = ErrorLog()
    tdrFolder = Folder("TDRFiles")
    tdrFilename = Filename(tdrFolder, "MultiplePTOsTDR.dcs")
    session_cleanup.append("TDRFiles")

    assert tdr.Write(
        tdrFilename, errorlog
    ), f"Simple TDR Template Example unable to write DICOS File : {tdrFilename}\n{errorlog.GetErrorLog().Get()}"

    tdrRead = TDR()
    errorlog = ErrorLog()

    assert tdrRead.Read(
        tdrFilename, errorlog, None
    ), f"Unable to read TDR file {tdrFilename}\n{errorlog.GetErrorLog().Get()}"

    assert (
        tdrRead == tdr
    ), f"TDR file loaded from {tdrFilename} does not match original.\n{errorlog.GetErrorLog().Get()}"


def test_ct_linked_tdr(session_cleanup):
    bRes = True
    ct = CT()
    tdr = TDR()
    strDate = DcsDate(DcsDate.Today())
    strTime = DcsTime(DcsTime.Now())
    vecRowOrientation = Vector3Dfloat()
    vecColumnOrientation = Vector3Dfloat()
    nPTOIdentifier1 = 0
    nPTOIdentifier2 = 1

    bRes = bRes and ct.SetOOIID(DcsLongString("10"))
    ct.GenerateSopInstanceUID()
    ct.GenerateScanInstanceUID()
    ct.GenerateSeriesInstanceUID()

    bRes = bRes and ct.SetImageAcquisitionDateAndTime(strDate, strTime)
    ct.SetBurnedInAnnotation(False)
    # The PHOTOMETRIC_INTERPRETATION enumeration is situated in the binding code of the CT Module.
    bRes = bRes and ct.SetPhotometricInterpretation(
        CT.PHOTOMETRIC_INTERPRETATION.enumMonochrome2
    )
    # The OOI_IMAGE_CHARACTERISTICS enumeration is situated in the binding code of the CT Module.
    bRes = bRes and ct.SetImageType(CT.OOI_IMAGE_CHARACTERISTICS.enumPhotoelectric)
    bRes = bRes and ct.SetImageAcquisitionDuration(5000)
    bRes = bRes and ct.SetContentDateAndTime(strDate, strTime)
    bRes = bRes and ct.SetOOIIDAssigningAuthority(
        DcsLongString("OOI ID Assigning Authority")
    )
    # The OBJECT_OF_INSPECTION_ID_TYPE enumeration is situated in the binding code of the TDR Module.
    bRes = bRes and ct.SetOOIIDType(TDR.OBJECT_OF_INSPECTION_ID_TYPE.enumRFID)
    # The OBJECT_OF_INSPECTION_TYPE enumeration is situated in the binding code of the CT Module.
    bRes = bRes and ct.SetOOIType(CT.OBJECT_OF_INSPECTION_TYPE.enumTypeBaggage)
    bRes = bRes and ct.SetScanID(DcsShortString("Scan ID"))
    bRes = bRes and ct.SetScanStartDateAndTime(strDate, strTime)
    # The SCAN_TYPE enumeration is situated in the binding code of the CT Module.
    bRes = bRes and ct.SetScanType(CT.SCAN_TYPE.enumOperational)
    bRes = bRes and ct.SetSeriesDateAndTime(strDate, strTime)
    # The ACQUISITION_STATUS enumeration is situated in the binding code of the GeneralSeriesModule Module.
    bRes = bRes and ct.SetSeriesAcquisitionStatus(
        GeneralSeriesModule.ACQUISITION_STATUS.enumSuccessful
    )
    bRes = bRes and ct.SetDeviceCalibrationDateAndTime(strDate, strTime)
    bRes = bRes and ct.SetDeviceSerialNumber(DcsLongString("123456987"))
    bRes = bRes and ct.SetMachineAddress(DcsShortText("Machine Address"))
    bRes = bRes and ct.SetMachineLocation(DcsLongString("Machine Location"))
    bRes = bRes and ct.SetMachineID(DcsShortString("Machine ID"))
    bRes = bRes and ct.SetDeviceManufacturer(DcsLongString("Device Manufacturer"))
    bRes = bRes and ct.SetDeviceManufacturerModelName(
        DcsLongString("Device Manufacturer Model Name")
    )
    bRes = bRes and ct.SetDeviceSoftwareVersion(
        DcsLongString("Device Software Version")
    )
    bRes = bRes and ct.SetSopInstanceCreationDateAndTime(strDate, strTime)

    ct.SetNumberOfSections(1)
    psection = ct.GetSectionByIndex(0)

    # The FILTER_MATERIAL enumeration is situated in the binding code of the Section Module.
    psection.SetFilterMaterial(Section.FILTER_MATERIAL.enumAluminum)
    psection.SetFocalSpotSizeInMM(10)
    psection.SetKVP(7000)

    vecRowOrientation.Set(1, 0, 0)
    vecColumnOrientation.Set(0, 1, 0)

    psection.SetPlaneOrientation(vecRowOrientation, vecColumnOrientation)

    # The IMAGE_DATA_TYPE enumeration is situated in the binding code of the Volume Module.
    psection.GetPixelData().Allocate(
        Volume.IMAGE_DATA_TYPE.enumUnsigned16Bit, 500, 500, 500
    )
    psection.GetPixelData().GetUnsigned16().Zero(0)

    ptFirstFrameTopLeft = Point3Dfloat(-250, -250, -250)

    psection.SetPositionInMM(ptFirstFrameTopLeft)
    psection.SetSpacingInMM(1.0, 1.0, 1.0)
    # S_UINT16 in Point3DS_UINT16 means that the type of the components of Point3D is S_UINT16
    # the supported types of Point3D are : S_UINT8, S_INT8, S_UINT16, S_INT16, float
    ptCenter = Point3DS_UINT16(250, 250, 250)

    nWhite = 0xFFFF
    vVolume = psection.GetPixelData().GetUnsigned16()
    ptPos = Point3DS_UINT16()

    for ptPos.z in range(200):
        pSlice = vVolume.GetSlice(ptPos.z)
        for ptPos.y in range(20):
            for ptPos.x in range(50):
                pSlice.Set(ptPos.y, ptPos.x, nWhite)

    for ptPos.z in range(ptCenter.z - 40, ptCenter.z + 40):
        pSlice = vVolume.GetSlice(ptPos.z)
        for ptPos.y in range(ptCenter.y - 40, ptCenter.y + 40):
            for ptPos.x in range(ptCenter.x - 40, ptCenter.x + 40):
                pSlice.Set(ptPos.y, ptPos.x, nWhite)

    for ptPos.z in range(ptCenter.z - 5, ptCenter.z + 5):
        pSlice = vVolume.GetSlice(ptPos.z)
        for ptPos.y in range(ptCenter.y - 5, ptCenter.y + 5):
            for ptPos.x in range(ptCenter.x + 41, ptCenter.x + 51):
                pSlice.Set(ptPos.y, ptPos.x, nWhite)

    assert bRes, "Error setting CT values"

    bRes = True

    bRes = bRes and tdr.SetOOIID(ct.GetOOIID())
    bRes = bRes and tdr.SetScanInstanceUID(ct.GetScanInstanceUID())
    bRes = bRes and tdr.SetSeriesInstanceUID(ct.GetSeriesInstanceUID())

    tdr.GenerateSopInstanceUID()

    bRes = bRes and tdr.SetFrameOfReferenceUID(ct.GetFrameOfReferenceUID())
    # The ThreatType enumeration is situated in the binding code of the TDR Module.
    bRes = bRes and tdr.AddPotentialThreatObject(
        nPTOIdentifier1, TDR.ThreatType.enumThreatTypeBaggage
    )
    # The ThreatType enumeration is situated in the binding code of the TDR Module.
    bRes = bRes and tdr.AddPotentialThreatObject(
        nPTOIdentifier2, TDR.ThreatType.enumThreatTypeBaggage
    )

    bRes = bRes and tdr.AddReferencedInstance(
        nPTOIdentifier1, ct.GetSopClassUID(), ct.GetSopInstanceUID(), 0
    )
    bRes = bRes and tdr.AddReferencedInstance(
        nPTOIdentifier2, ct.GetSopClassUID(), ct.GetSopInstanceUID(), 0
    )

    # The ASSESSMENT_FLAG enumeration is situated in the binding code of the TDR Module.
    # The THREAT_CATEGORY enumeration is situated in the binding code of the TDR Module.
    # The ABILITY_ASSESSMENT enumeration is situated in the binding code of the TDR Module.
    bRes = bRes and tdr.AddPTOAssessment(
        nPTOIdentifier1,
        TDR.ASSESSMENT_FLAG.enumThreat,
        TDR.THREAT_CATEGORY.enumProhibitedItem,
        TDR.ABILITY_ASSESSMENT.enumNoInterference,
        DcsLongText("Weapon"),
        float(98.0 / 100.0),
    )

    bRes = bRes and tdr.AddPTOAssessment(
        nPTOIdentifier2,
        TDR.ASSESSMENT_FLAG.enumNoThreat,
        TDR.THREAT_CATEGORY.enumAnomaly,
        TDR.ABILITY_ASSESSMENT.enumNoInterference,
        DcsLongText(""),
        float(-10),
    )

    # float in Array1DPoint3D means that the type of the components of Array1DPoint3D is float
    # the supported types of Array1DPoint3D are : S_UINT8, S_INT8, S_UINT16, S_INT16, float
    # Array1DPoint3D means that the type of the components of Array1D is Point3D
    bounds = Array1DPoint3Dfloat()
    bounds.SetSize(2, False)

    bounds[0] = Point3Dfloat(-250, -250, -250)
    bounds[1] = Point3Dfloat(-200, -230, -50)

    bRes = bRes and tdr.SetThreatBoundingPolygon(0, bounds, 0)

    bounds[0] = Point3Dfloat(float(-40), float(-40), float(-40))
    bounds[1] = Point3Dfloat(float(40), float(40), float(40))

    bRes = bRes and tdr.SetThreatBoundingPolygon(1, bounds, 0)

    ptBase = Point3Dfloat()
    ptExtents = Point3Dfloat()

    ptBase.Set(1, 2, 3)
    ptExtents.Set(50, 20, 200)

    bRes = bRes and tdr.SetThreatRegionOfInterest(
        nPTOIdentifier1, ptBase, ptExtents, Bitmap(), 0
    )
    bRes = bRes and tdr.SetBaggagePTODetails(nPTOIdentifier1, 1000, 5000, 0)
    bRes = bRes and tdr.SetBaggagePTOLocationDescription(
        nPTOIdentifier1, DcsShortText("Corner Object"), 0
    )

    ptBase.Set(210, 210, 210)
    ptExtents.Set(81, 81, 81)

    bRes = bRes and tdr.SetThreatRegionOfInterest(
        nPTOIdentifier2, ptBase, ptExtents, Bitmap(), 0
    )
    bRes = bRes and tdr.SetBaggagePTODetails(nPTOIdentifier2, 20, 2, 0)
    bRes = bRes and tdr.SetBaggagePTOLocationDescription(
        nPTOIdentifier2, DcsShortText("Corner Object"), 0
    )

    bRes = bRes and tdr.SetProcessingStartTime(
        nPTOIdentifier1, DcsDateTime(DcsDate.Today(), DcsTime.Now())
    )
    bRes = bRes and tdr.SetProcessingEndTime(
        nPTOIdentifier1, DcsDateTime(DcsDate.Today(), DcsTime.Now())
    )
    bRes = bRes and tdr.SetProcessingStartTime(
        nPTOIdentifier2, DcsDateTime(DcsDate.Today(), DcsTime.Now())
    )
    bRes = bRes and tdr.SetProcessingEndTime(
        nPTOIdentifier2, DcsDateTime(DcsDate.Today(), DcsTime.Now())
    )

    bRes = bRes and tdr.SetInstanceNumber(0)
    bRes = bRes and tdr.SetContentDateAndTime(strDate, strTime)
    bRes = bRes and tdr.SetTDRType(TDR.TDR_TYPE.enumMachine)
    bRes = bRes and tdr.SetTDRTypeATR(
        DcsLongString("ATR Manufacturer"), DcsLongString("ATR Version")
    )

    bRes = bRes and tdr.SetImageScaleRepresentation(1)

    bRes = bRes and tdr.SetAlarmDecision(TDR.ALARM_DECISION.enumAlarm)
    bRes = bRes and tdr.SetAlarmDecisionDateTime(strDate, strTime)
    bRes = bRes and tdr.SetAbortFlag(TDR.ABORT_FLAG.enumSuccess)
    bRes = bRes and tdr.SetTotalProcessingTimeInMS(50)
    bRes = bRes and tdr.SetOOIIDAssigningAuthority(ct.GetOOIIDAssigningAuthority())
    bRes = bRes and tdr.SetOOIIDType(ct.GetOOIIDType())
    bRes = bRes and tdr.SetOOIType(ct.GetOOIType())
    bRes = bRes and tdr.SetScanID(ct.GetScanID())
    bRes = bRes and tdr.SetScanStartDateAndTime(
        ct.GetScanStartDate(), ct.GetScanStartTime()
    )
    bRes = bRes and tdr.SetScanType(ct.GetScanType())
    bRes = bRes and tdr.SetSeriesDateAndTime(ct.GetSeriesDate(), ct.GetSeriesTime())
    bRes = bRes and tdr.SetSeriesAcquisitionStatus(ct.GetSeriesAcquisitionStatus())
    bRes = bRes and tdr.SetDeviceCalibrationDateAndTime(strDate, strTime)
    bRes = bRes and tdr.SetDeviceSerialNumber(DcsLongString("TDR Serial Number"))
    bRes = bRes and tdr.SetMachineAddress(DcsShortText("TDR machine address"))
    bRes = bRes and tdr.SetMachineLocation(DcsLongString("TDR machine location"))
    bRes = bRes and tdr.SetMachineID(DcsShortString("TDR machine ID"))
    bRes = bRes and tdr.SetDeviceManufacturer(DcsLongString("TDR device manufacturer"))
    bRes = bRes and tdr.SetDeviceManufacturerModelName(DcsLongString("TDR model name"))
    bRes = bRes and tdr.SetDeviceSoftwareVersion(DcsLongString("TDR software version"))
    bRes = bRes and tdr.SetSopInstanceCreationDateAndTime(strDate, strTime)

    assert bRes, "Error setting TDR values"

    folder = Folder("CTwithTDR")
    filenameCT = Filename(folder, "CT.dcs")
    filenameTDR = Filename(folder, "TDR.dcs")
    session_cleanup.append("CTwithTDR")

    errorlogCT = ErrorLog()
    errorlogTDR = ErrorLog()

    assert ct.Write(
        filenameCT, errorlogCT
    ), f"Failed writing CT (CTwithTDR) : {filenameCT}\n{errorlogCT.GetErrorLog().Get()}"

    assert tdr.Write(
        filenameTDR, errorlogTDR, CT.TRANSFER_SYNTAX.enumLittleEndianExplicit
    ), f"Failed writing TDR (CTwithTDR) : {filenameTDR}\n{errorlogTDR.GetErrorLog().Get()}"


if __name__ == "__main__":
    test_no_threat_tdr()
    test_baggage_tdr()
    test_multiple_ptos_tdr()
    test_ct_linked_tdr()