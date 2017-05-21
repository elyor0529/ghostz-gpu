/*
 * mpi_common.h
 * Created on 2017/05/16
 *    Auther:goto
 */

#ifndef MPI_COMMON_H_
#define MPI_COMMON_H_

#include "aligner_common.h"
#include "resource_deliverer.h"
#include "mpi_resource.h"

#include "mpi.h"
#include <string>
#include <fstream>

class MPICommon{
 public:
	struct MPIParameter{
		int rank;
		int size;
		int loadedDatabaseChunk;
		int loadedQueryBlock;
		
	};
	/*
	struct QueryResource{
		char *data;
		int ptr;
		int size;
		int chunk_id;
		bool available;
	};
	
	struct MasterResources{
		std::string query_filename;
		std::vector<QueryResource> query_list;
		
	};

	struct WorkerResources{
		std::vector<QueryResource> query_list;
	};
	
	*/
	typedef MPIResource::QueryResource QueryResource;
	typedef MPIResource::DatabaseResource DatabaseResource;
	typedef MPIResource::DatabaseInfo DatabaseInfo;
	typedef MPIResource::MasterResources MasterResources;
	typedef MPIResource::WorkerResources WorkerResources;
	typedef MPIResource::AlignmentTask AlignmentTask;
	
	typedef AlignerCommon::AligningCommonParameters AligningParameters;
	typedef AlignerCommon::Result Result;
	
	
	void debug(int argc,char *argv[]);

	void Run(std::string &queries_filename, std::string &database_filename,
			 std::string &output_filename,
			 AligningParameters &parameter,MPIParameter &mpi_parameter);
	void RunGPU(std::string &queries_filename,std::string &database_filename,
				std::string &output_file,
				AligningParameters &parameter,MPIParameter &mpi_parameter);
	static void LoadQueryResource(MasterResources &resources, int chunk_id);
	static void UnloadQueryResource(MasterResources &resources,int chunk_id);
private:
	
	
	void RunMaster(std::string &queries_filename,std::string &database_filename,
				   std::string &output_filename,
				   AligningParameters &parameter,MPIParameter &mpi_parameter);
	void RunWorker(AligningParameters &parameter,MPIParameter &mpi_parameter);

	void RunWorkerGPU(AligningParameters &parameter,MPIParameter &mpi_parameter);
	
	void SetupMasterResources(std::string &queries_filename, std::string &database_filename,
							  MasterResources &resources, AligningParameters &parameter,
							  MPIParameter &mpi_parameter);
	
	void SetupWorkerResources(WorkerResources &resources,MPIParameter &mpi_parameter);

	void AcceptCommand(MasterResources &resources);
	void AcceptRequestQuery(int cmd[2], MasterResources &resources,MPI::Status &status);
	void AcceptRequestDatabase(int cmd[2], MasterResources &resources,MPI::Status &status);
	void AcceptRequestTask(int cmd[2], MasterResources &resources,MPI::Status &status);
	
	void UpdateTaskBalance(MasterResources &resources);
	void GetNextTask(MasterResources &resources,int target,AlignmentTask &task);

	
	void LoadDatabaseResource(MasterResources &resources,int chunk_id);
	void UnloadDatabaseResource(MasterResources &resources,int chunk_id);
	void loadFileData(std::string filename, char **ptr,uint64_t *size);

	
	bool BuildParameters(int argc,char *argv[],std::string &input_filename,
						 std::string &database_filename,std::string &output_filename,
						 AligningParameters &par1ameters);
	
	void BuildQueryChunkPointers(std::string &queries_filename,
								 std::vector<int> &chunk_pointer_list,
								 std::vector<int> &chunk_size_list,AligningParameters &parameter);
	//	void RequestTask();
	//void LoadResource();
	
	
	
};



#endif