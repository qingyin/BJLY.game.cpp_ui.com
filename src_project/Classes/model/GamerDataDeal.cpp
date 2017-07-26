#include "GamerDataDeal.h"
#include "tool/Tools.h"

GamerDataDeal* GamerDataDeal::m_gamerDataDeal = nullptr;
GamerDataDeal* GamerDataDeal::getInstance()
{
    if(m_gamerDataDeal == nullptr)
    {
        m_gamerDataDeal = new GamerDataDeal();
    }
    return m_gamerDataDeal;
}
void GamerDataDeal::addGamerData(const int uid,GamerData* pGamerData)
{
    map<int,GamerData*>::iterator it = m_gamerDataM.find(uid);
    BYTE viewId = GetViewID(GamerData::getInstance()->getSeatId(),pGamerData->getSeatId());
    pGamerData->setViewId(viewId);
    if (it == m_gamerDataM.end())	
    { 
        m_gamerDataM.insert(make_pair(uid,pGamerData));
        m_gamerDataMSeat.insert(make_pair(pGamerData->getViewId(),pGamerData));
    }
    else
    { 
        m_gamerDataM[uid] = pGamerData;
        m_gamerDataMSeat[pGamerData->getViewId()] = pGamerData;
    }

    int num = m_gamerDataM.size();
}

void   GamerDataDeal::removeGamerData(const int uid)
{  
    map<int,GamerData*>::iterator it = m_gamerDataM.find(uid);
    if(it == m_gamerDataM.end()) 
    {
        return; 
    }
    GamerData*  pGamerData =  it->second;
    int viewid = pGamerData->getViewId();
    CC_SAFE_DELETE(pGamerData);
    m_gamerDataM.erase(uid);
    m_gamerDataMSeat.erase(viewid);
    int num = m_gamerDataM.size();
}
GamerData* GamerDataDeal::getGamerData(const int uid)
{
    map<int,GamerData*>::iterator it = m_gamerDataM.find(uid);
    if (it == m_gamerDataM.end())
    {
        return NULL;
    }
    else
    {
        return it->second;
    }
    return NULL;
}

GamerData* GamerDataDeal::getGamerDataBySeat(const int viewid)
{
    map<int,GamerData*>::iterator it = m_gamerDataMSeat.find(viewid);
    if (it == m_gamerDataMSeat.end())
    {
        return NULL;
    }
    else
    {
        return it->second;
    }
    return NULL;
}

void   GamerDataDeal::removeallGamerData()
{
    for(map <int,GamerData*>::iterator it = m_gamerDataM.begin(); it != m_gamerDataM.end(); ++it)
    {
        GamerData*  pGamerData =  it->second;
        CC_SAFE_DELETE(pGamerData);
    }
    m_gamerDataM.clear();
    m_gamerDataMSeat.clear();
}
