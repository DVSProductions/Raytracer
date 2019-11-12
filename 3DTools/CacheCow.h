//#pragma once
//#include <cstdint>
//#include <thread>
//#include <memory>
//#include <string>
//#include <Windows.h>
//#include <vector>
//#include <bitset>
//#include <Sphere.h>
//#include <mutex>
//constexpr bool IsCointainedIn(const KAFFINITY& subject, const KAFFINITY& container) noexcept {
//	return (subject & container) == subject;
//}
//class Cache {
//public:
//	GROUP_AFFINITY Owner;
//	int level;
//	/// <summary>
//	/// The cache line size, in bytes.
//	/// </summary>
//	int lineSize;
//	/// <summary>
//	/// 
//	/// <see cref="CacheUnified"/>
//	/// The cache is unified.
//	/// 
//	/// <para>
//	///		<see cref="CacheInstruction"/>
//	///		The cache is for processor instructions.
//	/// </para>
//	/// 
//	/// <see cref="CacheData"/>
//	/// The cache is for data.
//	/// 
//	/// <para>
//	///		<see cref="CacheTrace"/>
//	///		The cache is for traces.
//	/// </para>
//	/// 
//	/// </summary>
//	PROCESSOR_CACHE_TYPE type;
//	/// <summary>
//	/// The cache size, in bytes.
//	/// </summary>
//	DWORD Size;
//	/// <summary>
//	/// The cache associativity. If this member is CACHE_FULLY_ASSOCIATIVE (0xFF), the cache is fully associative.
//	/// </summary>
//	byte Associativity;
//	std::string toString(int depth) {
//		std::string padd = "\n";
//		for (int n = 0; n < depth; n++)padd += "\t";
//		return ""
//			+ padd + "Owner         " + std::bitset<32>(Owner.Mask).to_string()
//			+ padd + "level         " + std::to_string(level)
//			+ padd + "lineSize      " + std::to_string(lineSize)
//			+ padd + "Size          " + std::to_string(Size)
//			+ padd + "Type          " + std::to_string(type)
//			+ padd + "Associativity " + std::bitset<8>(this->Associativity).to_string();
//	}
//};
//class Core {
//public:
//	std::vector<Cache> Caches;
//	/// <summary>
//	/// A bitmap that specifies the affinity for zero or more processors within the specified group.
//	/// </summary>
//	KAFFINITY ID;
//	int threads;
//	/// <summary>
//	/// This is LTP_PC_SMT if the core has more than one logical processor, or 0 if the core has one logical processor. 
//	/// </summary>
//	std::bitset<8>flags;
//	/// <summary>
//	/// This member specifies the number of entries in the GroupMask array. 
//	/// </summary>
//	int GroupCount;
//	int Group;
//	/// <summary>
//	/// EfficiencyClass specifies the intrinsic tradeoff between performance and power for the applicable core. A core with a higher value for the efficiency class has intrinsically greater performance and less efficiency than a core with a lower value for the efficiency class. EfficiencyClass is only nonzero on systems with a heterogeneous set of cores.
//	/// </summary>
//	int EfficiencyClass;
//	bool isInCore(Cache c) {
//		return IsCointainedIn(c.Owner.Mask, ID);
//	}
//	std::string toString(int depth) {
//		std::string padd = "\n";
//		for (int n = 0; n < depth; n++)padd += "\t";
//		std::string ret = ""
//			+ padd + "ID              " + std::bitset<32>(ID).to_string()
//			+ padd + "Group           " + std::to_string(Group)
//			+ padd + "threads         " + std::to_string(threads)
//			+ padd + "GroupCount      " + std::to_string(GroupCount)
//			+ padd + "Flags           " + flags.to_string()
//			+ padd + "EfficiencyClass " + std::to_string(EfficiencyClass);
//		size_t idx = 0;
//		for (auto c : Caches)
//			ret += padd + "Cache[" + std::to_string(idx++) + "]" + c.toString(depth + 1);
//		return ret;
//	}
//};
//class NumaNode {
//public:
//	/// <summary>
//	/// The number of the NUMA node.
//	/// </summary>
//	int NodeNumber;
//	KAFFINITY Children;
//	std::vector<Core> Cores;
//	std::vector<Cache> SharedCache;
//	int Group;
//	bool isInNode(Core c) {
//		return IsCointainedIn(c.ID, Children);
//	}
//	bool isInNode(Cache c) {
//		return IsCointainedIn(c.Owner.Mask, Children);
//	}
//	std::string toString(int depth) {
//		std::string padd = "\n";
//		for (int n = 0; n < depth; n++)padd += "\t";
//		std::string ret = ""
//			+ padd + "NodeNumber " + std::to_string(NodeNumber)
//			+ padd + "Group      " + std::to_string(Group)
//			+ padd + "Children   " + std::bitset<32>(Children).to_string();
//		size_t idx = 0;
//		for (auto c : Cores)
//			ret += padd + "Core[" + std::to_string(idx++) + "]" + c.toString(depth + 1);
//		idx = 0;
//		for (auto c : SharedCache)
//			ret += padd + "SharedCache[" + std::to_string(idx++) + "]" + c.toString(depth + 1);
//		return ret;
//	}
//};
//class Group {
//public:
//	KAFFINITY Children;
//	std::vector<NumaNode> Processors;
//	short ActiveProcessorCount;
//	short MaximumProcessorCount;
//	/// <summary>
//	/// The number of active groups on the system. This member indicates the number of PROCESSOR_GROUP_INFO structures in the GroupInfo array.
//	/// </summary>
//	short ActiveGroupCount;
//	/// <summary>
//	/// The maximum number of processor groups on the system.
//	/// </summary>
//	short MaximumGroupCount;
//	std::vector<PROCESSOR_GROUP_INFO> PGI;
//	std::string toString(int depth) {
//		std::string padd = "\n";
//		for (int n = 0; n < depth; n++)padd += "\t";
//		std::string ret = ""
//			+ padd + "ActiveProcessorCount  " + std::to_string(ActiveProcessorCount)
//			+ padd + "MaximumProcessorCount " + std::to_string(MaximumProcessorCount)
//			+ padd + "ActiveGroupCount      " + std::to_string(ActiveGroupCount)
//			+ padd + "MaximumGroupCount     " + std::to_string(MaximumGroupCount)
//			+ padd + "Children              " + std::bitset<32>(Children).to_string();
//		size_t idx = 0;
//		for (auto n : Processors)
//			ret += padd + "NumaNode[" + std::to_string(idx++) + "]" + n.toString(depth + 1);
//		idx = 0;
//		return ret;
//	}
//};
//
//std::vector<SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX> getSystemInfo(_LOGICAL_PROCESSOR_RELATIONSHIP relation) noexcept {
//	DWORD length = 0;
//	const BOOL result_first = GetLogicalProcessorInformationEx(relation, nullptr, &length);
//	std::unique_ptr< uint8_t[] > buffer(new uint8_t[length]);
//	const PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX info = reinterpret_cast<PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX>(buffer.get());
//	const BOOL result_second = GetLogicalProcessorInformationEx(relation, info, &length);
//	std::vector<SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX> ret;
//	size_t offset = 0;
//	int idx = 0;
//	do {
//		const PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX current_info = reinterpret_cast<PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX>(buffer.get() + offset);
//		SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX safe;
//		memcpy(&safe, current_info, current_info->Size);
//		ret.push_back(safe);
//		offset += current_info->Size;
//	} while (offset < length);
//	return ret;
//}
//
//void LoadNodes(std::vector<Group>* groups) {
//	const auto l = getSystemInfo(_LOGICAL_PROCESSOR_RELATIONSHIP::RelationNumaNode);
//	for (auto e : l) {
//		NumaNode n;
//		n.Children = e.NumaNode.GroupMask.Mask;
//		n.NodeNumber = e.NumaNode.NodeNumber;
//		n.Group = e.NumaNode.GroupMask.Group;
//		groups->at(n.Group).Processors.push_back(n);
//	}
//}
//void LoadCores(std::vector<Group>* groups) {
//	const auto l = getSystemInfo(_LOGICAL_PROCESSOR_RELATIONSHIP::RelationProcessorCore);
//	for (auto e : l) {
//		Core c;
//		c.EfficiencyClass = e.Processor.EfficiencyClass;
//		c.flags = e.Processor.Flags;
//		c.GroupCount = e.Processor.GroupCount;
//		c.Group = e.Processor.GroupMask->Group;
//		c.ID = e.Processor.GroupMask->Mask;
//		c.threads = std::bitset<sizeof(c.ID) * 8>(c.ID).count();
//		for (size_t i = 0, max = groups->at(c.Group).Processors.size(); i != max; i++) {
//			if (groups->at(c.Group).Processors.at(i).isInNode(c)) {
//				groups->at(c.Group).Processors.at(i).Cores.push_back(c);
//				break;
//			}
//		}
//	}
//}
//void LoadCache(std::vector<Group>* groups) {
//	const auto l = getSystemInfo(_LOGICAL_PROCESSOR_RELATIONSHIP::RelationCache);
//	for (auto e : l) {
//		Cache c;
//		c.Associativity = e.Cache.Associativity;
//		c.Size = e.Cache.CacheSize;
//		c.lineSize = e.Cache.LineSize;
//		c.level = e.Cache.Level;
//		c.Owner = e.Cache.GroupMask;
//		c.type = e.Cache.Type;
//		for (size_t n = 0, max = groups->at(c.Owner.Group).Processors.size(); n != max; n++) {
//			if (groups->at(c.Owner.Group).Processors.at(n).isInNode(c)) {
//				auto bs = std::bitset<sizeof(KAFFINITY) * 8>(c.Owner.Mask);
//				auto cc = bs.count();//core count for this cache
//				for (size_t core = 0, cmax = groups->at(c.Owner.Group).Processors.at(core).Cores.size(); core != cmax; core++) {
//					if (groups->at(c.Owner.Group).Processors.at(n).Cores.at(core).threads == cc) {
//						if (groups->at(c.Owner.Group).Processors.at(n).Cores.at(core).isInCore(c)) {
//							groups->at(c.Owner.Group).Processors.at(n).Cores.at(core).Caches.push_back(c);
//							break;
//						}
//					}
//					else {
//						groups->at(c.Owner.Group).Processors.at(n).SharedCache.push_back(c);
//						break;
//					}
//				}
//				break;
//			}
//		}
//	}
//}
//std::vector<Group> CreateGroups() {
//	const auto l = getSystemInfo(_LOGICAL_PROCESSOR_RELATIONSHIP::RelationGroup);
//	std::vector<Group> ret;
//	for (auto e : l) {
//		Group g;
//		g.ActiveProcessorCount = e.Group.GroupInfo->ActiveProcessorCount;
//		g.Children = e.Group.GroupInfo->ActiveProcessorMask;
//		g.MaximumProcessorCount = e.Group.GroupInfo->MaximumProcessorCount;
//		g.ActiveGroupCount = e.Group.ActiveGroupCount;
//		g.MaximumGroupCount = e.Group.MaximumGroupCount;
//		size_t offset = 0;
//		do {
//			const PPROCESSOR_GROUP_INFO  current_info = reinterpret_cast<PPROCESSOR_GROUP_INFO>(e.Group.GroupInfo + offset);
//			PROCESSOR_GROUP_INFO safe;
//			memcpy(&safe, current_info, sizeof(PROCESSOR_GROUP_INFO));
//			g.PGI.push_back(safe);
//			offset += sizeof(PROCESSOR_GROUP_INFO);
//		} while (offset < g.MaximumGroupCount);
//		ret.push_back(g);
//	}
//	LoadNodes(&ret);
//	LoadCores(&ret);
//	LoadCache(&ret);
//	return ret;
//}
//struct sRect {
//	short top, left, bottom, right;
//};
//
//class CacheCow {
//	class L1Worker {
//		std::unique_ptr<DDD::Scene> Scene;
//		Cache myCache;
//	public:
//		L1Worker(const std::shared_ptr<DDD::Scene>& globalScene, Cache target) {
//			Scene = std::make_unique<DDD::Scene>(globalScene->clone());
//			myCache = target;
//		}
//		void launch() {
//
//		}
//	};
//	class L2Worker {
//		std::mutex waiter;
//		std::shared_ptr<DDD::Scene> Scene;
//		std::vector<L1Worker> targetThreads;
//		std::unique_ptr<std::thread>managementThread;
//		void loadCaches() {
//			for (auto c : subcaches) {
//				if (c.level == 1)
//					targetThreads.push_back(L1Worker(Scene, c));
//				else
//					myCache = c;
//			}
//		}
//	public:
//		Cache myCache;
//		std::vector<Cache> subcaches;
//		L2Worker(std::shared_ptr<DDD::Scene> globalScene) {
//			Scene = globalScene;
//			//myCache = target;
//		}
//		void launch() {
//			loadCaches();
//			waiter.lock();
//			managementThread = std::make_unique<std::thread>(std::thread(&L2Worker::internalLogic, this));
//			SetThreadAffinityMask(managementThread->native_handle(), myCache.Owner.Mask);
//			waiter.unlock();
//		}
//		void internalLogic() {
//			waiter.lock();
//			const size_t siz = targetThreads.size();
//			for (size_t n = 0; n != siz; n++)
//				targetThreads.at(n).launch();
//		}
//	};
//	class L3Worker {
//		/// <summary>
//		/// Syncronizes the Thread to begin once initialization is done
//		/// </summary>
//		std::mutex waiter;
//		Cache myCache;
//		sRect RenderArea;
//		std::vector<L2Worker> targetCores;
//		std::unique_ptr<std::thread>managementThread;
//	public:
//		L3Worker(std::shared_ptr<DDD::Scene> globalScene, Cache target, std::vector<Cache> subcaches) {
//			myCache = target;
//			for (auto c : subcaches) {
//				if (IsCointainedIn(c.Owner.Mask, myCache.Owner.Mask)) {
//					const size_t siz = targetCores.size();
//					bool found = false;
//					for (size_t n = 0; n != siz && !found; n++) {
//						if (targetCores.at(n).myCache.Owner.Mask == c.Owner.Mask) {
//							targetCores.at(n).subcaches.push_back(c);
//							found = true;
//						}
//					}
//					if (!found) {
//						L2Worker L2(globalScene);
//						L2.myCache.Owner = c.Owner;
//						L2.subcaches.push_back(c);
//						targetCores.push_back(L2);
//					}
//				}
//			}
//		}
//		void launch(Group target) {
//			waiter.lock();
//			managementThread = std::make_unique<std::thread>(std::thread(&L3Worker::internalLogic, this));
//			/*GROUP_AFFINITY myGA;
//			GetThreadGroupAffinity(managementThread->native_handle(), &myGA);
//			myGA.
//			SetThreadGroupAffinity(managementThread->native_handle(), &myGA);*/
//			//Assigns this thread to all available cores that work for this L3 Cache
//			SetThreadAffinityMask(managementThread->native_handle(), myCache.Owner.Mask);
//			waiter.unlock();
//		}
//		/// <summary>
//		/// Creates and manages workers for L2 cache.
//		/// </summary>
//		void internalLogic() {
//			waiter.lock();
//			const size_t siz = targetCores.size();
//			for (size_t n = 0; n != siz; n++)
//				targetCores.at(n).launch();
//		}
//	};
//	uint8_t corecount;
//	uint8_t threadsPerCore;
//	std::vector<L3Worker> udders;
//public:
//	CacheCow() {
//
//	}
//	void init() {
//		auto CPU_INFO = CreateGroups();
//		for (auto Group : CPU_INFO) {
//			for (auto Numa : Group.Processors) {
//				for (auto L3Cache : Numa.SharedCache) {
//					//udders.push_back(L3Worker())
//				}
//			}
//		}
//		return;
//	}
//
//};
//
