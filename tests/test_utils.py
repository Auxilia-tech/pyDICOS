from typing import Dict, List

import numpy as np
from pydicos import DicosDateTime, TDR_DATA_TEMPLATE
from pyDICOS import DcsDateTime, ALARM_DECISION, SCAN_TYPE, ABILITY_ASSESSMENT, THREAT_CATEGORY, ASSESSMENT_FLAG
from datetime import datetime


def test_datetime():
    t = DicosDateTime()
    assert str(t) == "0-00-00 00:00:00.0"
    assert repr(t) == "DicosDateTime({'date': (0, 0, 0), 'time': (0, 0, 0, 0)})"

    now = DcsDateTime()
    now.SetNow()
    pynow = datetime.now()
    t = DicosDateTime(datetime=now)
    assert str(t)[-5] == str(pynow)[-5]
    assert t.as_datetime() == pynow

def get_tdr_data_output_template() -> Dict:
    """
    Get a template for the output of a TDR data loader.
    """
    data = TDR_DATA_TEMPLATE.copy()

    data['ATR']['manufacturer'] = 'AUXILIA'
    data['ATR']['version'] = '1.0'
    data['ATR']['parameters'] = {   'param1':'-test=true' }
    data['OOIID'] = '12345-35345324-6326342-345'
    data['InstanceUID'] = '12345-35345324-6326342-345'
    data['ContentDateAndTime'] = {"date" : (2024, 10, 10), "time" : (12, 0, 0, 0)}
    data["ScanType"] = SCAN_TYPE.enumOperational
    data['AlarmDecisionDateTime'] = {"date" : (2024, 10, 10), "time" : (12, 0, 0, 0)}
    data['AlarmDecision'] = ALARM_DECISION.enumAlarm
    data['ProcessingTime'] = 800
    data['ImageScaleRepresentation'] = 1.0
    return data

def get_pto_data(id:int, base:List[float], extent:List[float], description:str, conf:float, bitmap:np.ndarray) -> Dict:
    """
    Get a template for the output of a PTO data loader.
    """
    data = {

        "ID": id,
        "Base": {
            "x": base[0],
            "y": base[1],
            "z": base[2],
        },
        "Extent":{
            "x": extent[0],
            "y": extent[1],
            "z": extent[2],
        },
        "Assessment": {
            'ability': ABILITY_ASSESSMENT.enumNoInterference,
            'category': THREAT_CATEGORY.enumProhibitedItem,
            'description': description,
            'flag': ASSESSMENT_FLAG.enumThreat,
            'probability': conf
        },
        "Bitmap": bitmap,
        "ReferencedInstance" : {
                "SopClassUID": "0",
                "SopInstanceUID": "0",
            },
        "PTOProcessingTime" : {
                "ProcessingStartTime" : {"date" : (2024, 10, 10), "time" : (12, 0, 0, 0)},
                "ProcessingEndTime" : {"date" : (2024, 10, 10), "time" : (12, 0, 0, 50)},
                "fTotalTimeMS" : 50
            }
        }

    return data
    
def set_alarm_decision(data:Dict) -> None:
    # Set the alarm decision
    data["AlarmDecision"] = ALARM_DECISION.enumAlarm if np.any([pto["Assessment"]["probability"] > 0.3 for pto in data["PTOs"]]) \
                else ALARM_DECISION.enumClear