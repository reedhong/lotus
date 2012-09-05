/********************************************************************
	created:	2012/08/29 
	filename: 	MeshSerializer.h
	author:		reedhong 
	
	purpose:	 用于Mesh的导入和导出
*********************************************************************/

#ifndef __Lotus_MeshSerializer_H__
#define __Lotus_MeshSerializer_H__

#include "General/Serializer.h"
#include "Mesh.h"

namespace Lotus {
	class MeshSerializer: public Serializer
	{
	public:
		MeshSerializer();
		MeshSerializer(StreamPtr stream);
		~MeshSerializer();
        void exportMesh(const Mesh* pMesh, StreamPtr stream);
        void importMesh(StreamPtr& stream, Mesh* pDest);

	protected:
		virtual void writeSubMeshNameTable(const Mesh* pMesh);
		virtual void writeMesh(const Mesh* pMesh);
		virtual void writeSubMesh(const SubMesh* s);
		virtual void writeSubMeshOperation(const SubMesh* s);
		virtual void writeSubMeshTextureAliases(const SubMesh* s);
		virtual void writeGeometry(const VertexData* pGeom);
		virtual void writeSkeletonLink(const String& skelName);
		virtual void writeMeshBoneAssignment(const VertexBoneAssignment& assign);
		virtual void writeSubMeshBoneAssignment(const VertexBoneAssignment& assign);
		virtual void writeLodInfo(const Mesh* pMesh);
		virtual void writeLodSummary(unsigned short numLevels, bool manual, const LodStrategy *strategy);
		virtual void writeLodUsageManual(const MeshLodUsage& usage);
		virtual void writeLodUsageGenerated(const Mesh* pMesh, const MeshLodUsage& usage, unsigned short lodNum);
		virtual void writeBoundsInfo(const Mesh* pMesh);
		virtual void writeEdgeList(const Mesh* pMesh);
		virtual void writeAnimations(const Mesh* pMesh);
		virtual void writeAnimation(const Animation* anim);
		virtual void writePoses(const Mesh* pMesh);
		virtual void writePose(const Pose* pose);
		virtual void writeAnimationTrack(const VertexAnimationTrack* track);
		virtual void writeMorphKeyframe(const VertexMorphKeyFrame* kf, size_t vertexCount);
		virtual void writePoseKeyframe(const VertexPoseKeyFrame* kf);
		virtual void writePoseKeyframePoseRef(const VertexPoseKeyFrame::PoseRef& poseRef);
		virtual void writeExtremes(const Mesh *pMesh);
		virtual void writeSubMeshExtremes(unsigned short idx, const SubMesh* s);

		virtual size_t calcMeshSize(const Mesh* pMesh);
		virtual size_t calcSubMeshSize(const SubMesh* pSub);
		virtual size_t calcGeometrySize(const VertexData* pGeom);
		virtual size_t calcSkeletonLinkSize(const String& skelName);
		virtual size_t calcBoneAssignmentSize(void);
		virtual size_t calcSubMeshOperationSize(const SubMesh* pSub);
		virtual size_t calcSubMeshNameTableSize(const Mesh* pMesh);
		virtual size_t calcEdgeListSize(const Mesh* pMesh);
		virtual size_t calcEdgeListLodSize(const EdgeData* data, bool isManual);
		virtual size_t calcEdgeGroupSize(const EdgeData::EdgeGroup& group);
		virtual size_t calcPosesSize(const Mesh* pMesh);
		virtual size_t calcPoseSize(const Pose* pose);
		virtual size_t calcAnimationsSize(const Mesh* pMesh);
		virtual size_t calcAnimationSize(const Animation* anim);
		virtual size_t calcAnimationTrackSize(const VertexAnimationTrack* track);
		virtual size_t calcMorphKeyframeSize(const VertexMorphKeyFrame* kf, size_t vertexCount);
		virtual size_t calcPoseKeyframeSize(const VertexPoseKeyFrame* kf);
		virtual size_t calcPoseKeyframePoseRefSize(void);
		virtual size_t calcPoseVertexSize(const Pose* pose);
		virtual size_t calcSubMeshTextureAliasesSize(const SubMesh* pSub);


		virtual void readTextureLayer(StreamPtr& stream, Mesh* pMesh, MaterialPtr& pMat);
		virtual void readSubMeshNameTable(StreamPtr& stream, Mesh* pMesh);
		virtual void readMesh(StreamPtr& stream, Mesh* pMesh);
		virtual void readSubMesh(StreamPtr& stream, Mesh* pMesh);
		virtual void readSubMeshOperation(StreamPtr& stream, Mesh* pMesh, SubMesh* sub);
		virtual void readSubMeshTextureAlias(StreamPtr& stream, Mesh* pMesh, SubMesh* sub);
		virtual void readGeometry(StreamPtr& stream, Mesh* pMesh, VertexData* dest);
		virtual void readGeometryVertexDeclaration(StreamPtr& stream, Mesh* pMesh, VertexData* dest);
		virtual void readGeometryVertexElement(StreamPtr& stream, Mesh* pMesh, VertexData* dest);
		virtual void readGeometryVertexBuffer(StreamPtr& stream, Mesh* pMesh, VertexData* dest);

		virtual void readSkeletonLink(StreamPtr& stream, Mesh* pMesh);
		virtual void readMeshBoneAssignment(StreamPtr& stream, Mesh* pMesh);
		virtual void readSubMeshBoneAssignment(StreamPtr& stream, Mesh* pMesh, 
			SubMesh* sub);
		virtual void readMeshLodInfo(StreamPtr& stream, Mesh* pMesh);
		virtual void readMeshLodUsageManual(StreamPtr& stream, Mesh* pMesh, 
			unsigned short lodNum, MeshLodUsage& usage);
		virtual void readMeshLodUsageGenerated(StreamPtr& stream, Mesh* pMesh, 
			unsigned short lodNum, MeshLodUsage& usage);
		virtual void readBoundsInfo(StreamPtr& stream, Mesh* pMesh);
		virtual void readEdgeList(StreamPtr& stream, Mesh* pMesh);
		virtual void readEdgeListLodInfo(StreamPtr& stream, EdgeData* edgeData);
		virtual void readPoses(StreamPtr& stream, Mesh* pMesh);
		virtual void readPose(StreamPtr& stream, Mesh* pMesh);
		virtual void readAnimations(StreamPtr& stream, Mesh* pMesh);
		virtual void readAnimation(StreamPtr& stream, Mesh* pMesh);
		virtual void readAnimationTrack(StreamPtr& stream, Animation* anim, 
			Mesh* pMesh);
		virtual void readMorphKeyFrame(StreamPtr& stream, VertexAnimationTrack* track);
		virtual void readPoseKeyFrame(StreamPtr& stream, VertexAnimationTrack* track);
		virtual void readExtremes(StreamPtr& stream, Mesh *pMesh);
#endif

	};
}


#endif
