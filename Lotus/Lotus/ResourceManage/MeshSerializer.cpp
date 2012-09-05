/********************************************************************
	created:	2012/08/29 
	filename: 	MeshSerializer.cpp
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#include "MeshSerializer.h"
#include "Exception/Exception.h"

namespace Lotus {
	const unsigned short HEADER_CHUNK_ID = 0x1000;
	MeshSerializer::MeshSerializer()
	{

	}

	MeshSerializer::MeshSerializer(StreamPtr stream):Serializer(stream)
	{

	}

	MeshSerializer::~MeshSerializer()
	{

	}

	void MeshSerializer::exportMesh(const Mesh* pMesh, StreamPtr stream)
	{

	}

	void MeshSerializer::importMesh(StreamPtr& stream, Mesh* pDest)
	{
		unsigned short headerID;
		readShorts(stream, &headerID, 1);
		if( headerID != HEADER_CHUNK_ID){
			LOTUS_EXCEPT(Exception::ERR_INTERNAL_ERROR, "header chunk id  error",
				"MeshSerializer::importMesh");
		}
		// todo, just skip now		
		String ver = readString(stream);
	
		readFileHeader(stream);

		unsigned short streamID;
		while( !stream->eof()){
			streamID = readChunk();
			if(streamID == M_MESH){
				readMesh(stream, pMesh);
				break;
			}
		}
	}
	
	//////////////////////////////////////////////////////////////////////////
	// read
	void MeshSerializer::readMesh(StreamPtr& stream, Mesh* pMesh)
	{
		bool skeletallyAnimated;
		readBools(stream, &skeletallyAnimated, 1);

		if( !stream->eof()){
			unsigned short streamID = readChunk(stream);
			while(!stream->eof() &&
				(streamID == M_GEOMETRY ||
				streamID == M_SUBMESH ||
				streamID == M_MESH_SKELETON_LINK ||
				streamID == M_MESH_BONE_ASSIGNMENT ||
				streamID == M_MESH_LOD ||
				streamID == M_MESH_BOUNDS ||
				streamID == M_SUBMESH_NAME_TABLE ||
				streamID == M_EDGE_LISTS ||
				streamID == M_POSES ||
				streamID == M_ANIMATIONS ||
				streamID == M_TABLE_EXTREMES))
			{
				switch(streamID){
				case M_GEOMETRY:
					pMesh->sharedVertexData = OGRE_NEW VertexData();
					try {
						readGeometry(stream, pMesh, pMesh->sharedVertexData);
					}
					catch (Exception& e)
					{
						if (e.getNumber() == Exception::ERR_ITEM_NOT_FOUND)
						{
							// duff geometry data entry with 0 vertices
							LOTUS_DELETE pMesh->sharedVertexData;
							pMesh->sharedVertexData = 0;
							// Skip this stream (pointer will have been returned to just after header)
							stream->skip(mCurrentstreamLen - MSTREAM_OVERHEAD_SIZE);
						}
						else
						{
							throw;
						}
					}
					break;				
				case M_SUBMESH:
					readSubMesh(stream, pMesh, listener);
					break;
				case M_MESH_SKELETON_LINK:
					readSkeletonLink(stream, pMesh, listener);
					break;
				}
			}
		}
	}

	void MeshSerializer::readGeometry(StreamPtr& stream, Mesh* pMesh, VertexData* dest)
	{

	}

	void MeshSerializer::readSubMesh(StreamPtr& stream, Mesh* pMesh)
	{

	}

	void MeshSerializer::readSkeletonLink(StreamPtr& stream, Mesh* pMesh)
	{

	}
	//////////////////////////////////////////////////////////////////////////
	// write


	//////////////////////////////////////////////////////////////////////////
	// calc
}

