#include <Server_Common/ExdData.h>
#include <Server_Common/Util.h>
#include <Server_Common/ServerPacketDef.h>
#include <Server_Common/Logger.h>
#include <Server_Common/ExdData.h>

#include <boost/algorithm/string.hpp>
#include <algorithm>

#include "Actor.h"

#include "StatusEffect.h"

extern Core::Logger g_log;
extern Core::Data::ExdData g_exdData;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

Core::StatusEffect::StatusEffect::StatusEffect( uint32_t id, Entity::ActorPtr sourceActor, Entity::ActorPtr targetActor,
                                                uint32_t duration, uint32_t tickRate )
   : m_id( id )
   , m_sourceActor( sourceActor )
   , m_targetActor( targetActor )
   , m_duration( duration )
   , m_startTime( 0 )
   , m_tickRate( tickRate )
   , m_lastTick( 0 )
{
   auto& entry = g_exdData.m_statusEffectInfoMap[id];
   m_name = entry.name;
      
   std::replace( m_name.begin(), m_name.end(), ' ', '_' );
   std::replace( m_name.begin(), m_name.end(), ':', '_' );
   std::replace( m_name.begin(), m_name.end(), '&', '_' );
   std::replace( m_name.begin(), m_name.end(), '+', 'p' );
   boost::erase_all( m_name, "\'" );
   boost::erase_all( m_name, "&" );
   boost::erase_all( m_name, "-" );
   boost::erase_all( m_name, "(" );
   boost::erase_all( m_name, ")" );
}


Core::StatusEffect::StatusEffect::~StatusEffect()
{
}


void Core::StatusEffect::StatusEffect::onTick()
{
   m_lastTick = Util::getTimeMs();
}

uint32_t Core::StatusEffect::StatusEffect::getSrcActorId() const
{
   return m_sourceActor->getId();
}

uint32_t Core::StatusEffect::StatusEffect::getTargetActorId() const
{
   return m_targetActor->getId();
}

void Core::StatusEffect::StatusEffect::applyStatus()
{
   m_startTime = Util::getTimeMs();

   // this is only right when an action is being used by the player
   // else you probably need to use an actorcontrol

   //GamePacketNew< FFXIVIpcEffect > effectPacket( m_sourceActor->getId() );
   //effectPacket.data().targetId = m_sourceActor->getId();
   //effectPacket.data().actionAnimationId = 3;
   //effectPacket.data().unknown_3 = 1;
   //effectPacket.data().actionTextId = 3;
   //effectPacket.data().unknown_5 = 1;
   //effectPacket.data().unknown_6 = 321;
   //effectPacket.data().rotation = ( uint16_t ) ( 0x8000 * ( ( m_sourceActor->getPos().getR() + 3.1415926 ) ) / 3.1415926 );
   //effectPacket.data().effectTargetId = m_sourceActor->getId();
   //effectPacket.data().effects[4].unknown_1 = 17;
   //effectPacket.data().effects[4].bonusPercent = 30;
   //effectPacket.data().effects[4].param1 = m_id;
   //effectPacket.data().effects[4].unknown_5 = 0x80;
   //m_sourceActor->sendToInRangeSet( effectPacket, true );

   g_log.debug( "StatusEffect applied: " + m_name );
}

void Core::StatusEffect::StatusEffect::removeStatus()
{
   g_log.debug( "StatusEffect removed: " + m_name );
}

uint32_t Core::StatusEffect::StatusEffect::getId() const
{
   return m_id;
}

uint32_t Core::StatusEffect::StatusEffect::getDuration() const
{
   return m_duration;
}

uint32_t Core::StatusEffect::StatusEffect::getTickRate() const
{
   return m_tickRate;
}

uint64_t Core::StatusEffect::StatusEffect::getLastTickMs() const
{
   return m_lastTick;
}

uint64_t Core::StatusEffect::StatusEffect::getStartTimeMs() const
{
   return m_startTime;
}

void Core::StatusEffect::StatusEffect::setLastTick( uint64_t lastTick )
{
   m_lastTick = lastTick;
}

const std::string& Core::StatusEffect::StatusEffect::getName() const
{
   return m_name;
}
