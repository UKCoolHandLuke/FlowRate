#include <Action_List.h>
#include <Action_Block.h>
#include <System.h>

Action_List::Action_List()
{

}

Action_List::~Action_List()
{
//Clear our action list

	while(this->size()>0)
	{
		Action *A = this->front();
		this->erase(this->begin());
		delete A;
	}

}


bool Action_List::Execute(Host *H, Threshold *T, Match *M)
{
	
	Action_Result R;

	//Create Action Block here ????

	Action_Block *Master_Block = new Action_Block();

	PortRange_List *SRC_Ports = M->SourcePort_List->Copy();
	PortRange_List *DST_Ports = M->DestinationPort_List->Copy();
	Protocol_List  *Proto_List = M->_Protocol_List->Copy();
	MATCH_STATUS Direction = M->Cache->GetMatchType();
	//long BanLength = T->getBan_Length();

	//We need to figure out the direction and protocol/port that were breached
	//For that we need to use the threshold 

	Master_Block->Host = H->HostAddress.to_string();
	Master_Block->ProtocolList = Proto_List->Copy();
	Master_Block->DST_Port_List = DST_Ports->Copy();
	Master_Block->SRC_Port_List = SRC_Ports->Copy();
	Master_Block->Direction = Direction;
	//Master_Block->RemovalTime = Master_Block->TimeAdded + BanLength;						    //Ban for this amount of time
	Master_Block->Rule_ID = M->Cache->GetID();// +Master_Block->Host;							//Name of the initiating rule	Master_Block->Unique_ID = M->Cache->GetID();
	Master_Block->Unique_ID = H->HostAddress.to_string();
	//Extended info
	Master_Block->Threshold = T->Copy();
	Master_Block->HostStackSize = H->Size();



	for (Int32 i = 0; i < size(); i++)
	{
		
		Action_Block *Block = new Action_Block;
		*Block = *Master_Block;	//clone our master block - 1 for each action
		//Each action must clean up the block when finished with it

		Action *A = this->at(i);
		R = A->Check_Then_Execute(Block);

		//R = A->Execute(H, T);
		//System::Logging.Writeln("Action_Result: " + R.Message,LogLevel::LOG_DEBUG);
	}


	//delete our master block
	delete Master_Block;

	return(true);
}