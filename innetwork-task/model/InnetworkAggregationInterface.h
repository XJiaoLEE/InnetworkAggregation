#ifndef INNETWORK_AGG_INTERFACE_H
#define INNETWORK_AGG_INTERFACE_H

#include <cstdint>
#include <functional>
#include <unordered_map>
#include "ns3/object.h"
#include "ns3/log.h"
#include "ns3/packet.h"
#include "ns3/quic-module.h"
#include "ns3/ipv4-address.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
//#include "datainnetwork.h"
#include "/home/jenny/workspace/ns-3-allinone/ns-3.37/src/innetwork-task/helper/parameter.h"
//#include "consumer.h"
//#include "producer.h"
//#include "aggregator.h"
#include "/home/jenny/workspace/ns-3-allinone/ns-3.37/src/innetwork-task/helper/vectorop.h"


// used for datatransfer by nodes
namespace ns3 {
    class InnetworkAggregationInterface : public Object {
            bool isEnd;
            uint8_t aggTreeLevel; // level of nodes in the aggregation tree or topology using the consumer as the root
            uint16_t m_peerPort; // remote port
            uint16_t vsize;
            Ptr<Node> node;
            uint16_t currentIteration;
            uint16_t maxIteration;
            std::ofstream outFile; //save result for server
            Time startTime; // record each start time

            std::vector<uint64_t> avg; // result
            std::vector<Address> cGroup; // nodes acts as clients with respect to current node
            std::vector<Address> sGroup; // nodes acts as servers with respect to current node
            std::unordered_map<uint8_t, ReceivedChunk> chunkMap; // chunk counting by chunkNumber and count
            std::unordered_map <std::string, Ptr<Application>> socketPool;
            uint8_t currentIndex;


        public:
            static TypeId GetTypeId (void);
            InnetworkAggregationInterface ();
            ~InnetworkAggregationInterface ();
            void SetupInnetworkAggregationInterface (uint16_t port, uint16_t itr, uint8_t aggTreeLevel, std::vector<Address> &sGroup, 
                                        std::vector<Address> &cGroup, Ptr<Node> node, bool isEnd);
            void CreateSocketPool (std::string cc_name);
            void ReceiveDataFrom (std::string fromStr);
            void ReceiveDataFromAll ();
            void HandleResponseV (std::string fromStr, uint8_t *buffer);
            void HandleRequestV (std::string fromStr);
            void SendRequestVTo (std::string toStr);
            void SendRequestVToAll ();
            void ScheduleAndSend();
            void SendResponseVToP (std::vector<uint64_t> &vec );
            void AVG ();
            void SendResponseVTo (std::string toStr, std::vector<uint64_t> &vec);
            void SetVSize (uint16_t size);
            void AvgEnd (uint16_t size);
            
            bool GetisEnd ();
            void SetisEnd (bool v);
            void ClearChunkMap ();
            void WriteChunk2Vec (std::vector<uint64_t> &vec, uint16_t size);
            void SaveResult (std::vector<uint64_t> &vec );
            void SetOutFile (const std::string fileName);
            void Addr2Str (Address addr, std::string &str);
            void DelayedSend(Ptr<QuicMyServer> responseptr, uint8_t* chunkBuffer, uint32_t bufferSize);
            void GoToReadPos(Ptr<CircularBuffer> ccircularBuffer);
    };

}; /*namespace ns3*/

#endif /*INNETWORK_AGG_INTERFACE_H*/