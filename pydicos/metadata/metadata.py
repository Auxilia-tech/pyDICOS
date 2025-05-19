from typing import Dict, List, Optional, Union, Any
from dataclasses import dataclass
from datetime import datetime
import numpy as np
from pathlib import Path

@dataclass
class BaseMetadata:
    """Base class for all metadata types."""
    pass

@dataclass
class DateTimeMetadata:
    """Metadata class for date and time information."""
    date: tuple[int, int, int]  # (year, month, day)
    time: tuple[int, int, int, int]  # (hour, minute, second, microsecond)

    @classmethod
    def from_datetime(cls, dt: datetime) -> 'DateTimeMetadata':
        """Create DateTimeMetadata from a datetime object."""
        return cls(
            date=(dt.year, dt.month, dt.day),
            time=(dt.hour, dt.minute, dt.second, dt.microsecond)
        )

    def to_datetime(self) -> datetime:
        """Convert to datetime object."""
        return datetime(
            self.date[0], self.date[1], self.date[2],
            self.time[0], self.time[1], self.time[2], self.time[3]
        )

@dataclass
class Point3D:
    """3D point metadata."""
    x: float
    y: float
    z: float

@dataclass
class PTOAssessment:
    """Potential Threat Object assessment metadata."""
    flag: int
    category: int
    ability: int
    description: str
    probability: float

@dataclass
class PTOReferencedInstance:
    """Potential Threat Object referenced instance metadata."""
    sop_class_uid: str
    sop_instance_uid: str

@dataclass
class PTOProcessingTime:
    """Potential Threat Object processing time metadata."""
    start_time: DateTimeMetadata
    end_time: DateTimeMetadata
    total_time_ms: float

@dataclass
class PTOMetadata:
    """Potential Threat Object metadata."""
    base: Point3D
    extent: Point3D
    bitmap: Optional[np.ndarray]
    polygon: List[Point3D]
    id: int
    assessment: Optional[PTOAssessment]
    referenced_instance: Optional[PTOReferencedInstance]
    processing_time: Optional[PTOProcessingTime]

@dataclass
class ATRMetadata:
    """ATR (Automatic Threat Recognition) metadata."""
    manufacturer: str
    version: str
    parameters: Dict[str, str]

@dataclass
class TDRMetadata(BaseMetadata):
    """TDR (Threat Detection Report) metadata."""
    instance_number: int
    instance_uid: str
    ooi_id: str
    content_date_time: DateTimeMetadata
    processing_time: float
    scan_type: int
    alarm_decision: int
    alarm_decision_date_time: DateTimeMetadata
    image_scale_representation: float
    atr: ATRMetadata
    tdr_type: int
    ooi_type: int
    ptos: List[PTOMetadata]

@dataclass
class CTMetadata(BaseMetadata):
    """CT (Computed Tomography) metadata."""
    instance_number: int
    instance_uid: str
    series_instance_uid: str
    frame_of_reference_uid: str
    ooi_id: str
    ooi_type: int
    content_date_time: DateTimeMetadata
    sop_class_uid: str

@dataclass
class DXMetadata(BaseMetadata):
    """DX (Digital X-ray) metadata."""
    instance_number: int
    instance_uid: str
    series_instance_uid: str
    frame_of_reference_uid: str
    ooi_id: str
    ooi_type: int
    content_date_time: DateTimeMetadata
    sop_class_uid: str 