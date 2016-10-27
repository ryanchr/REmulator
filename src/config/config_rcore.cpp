/*****************************************************************************
  config_rcore.cpp

  Original Author: Chen Ren, CNASIC, 2010-12-18
 *****************************************************************************/

#include "config_rcore.h"

/************ used for print information *************/
DataSegmentGroup::DataSegmentGroup(const DataSegmentGroup & data_seg_group)
{
	Uint32 size =	(Uint32)data_seg_group.data_context.size();

	for(Uint32 i=0; i<size; i++){
		DataSegmentCfg *temp = new DataSegmentCfg(*data_seg_group.data_context[i]);
		data_context.push_back(temp);
	}
}
DataSegmentGroup & DataSegmentGroup::operator =(const DataSegmentGroup & data_seg_group)
{
	Uint32 size =	(Uint32)data_seg_group.data_context.size();

	for(Uint32 i=0; i<size; i++){
		DataSegmentCfg *temp = new DataSegmentCfg(*data_seg_group.data_context[i]);
		data_context.push_back(temp);
	}
	return *this;
}