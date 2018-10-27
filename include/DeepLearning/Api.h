//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should be included directly in your program.
//

#pragma once

#include "ATL/Array.h"
#include "ATL/Optional.h"
#include "ATL/AtlString.h"
#include "ATL/AtlTypes.h"

#include "AVLCommon/Config.h"

#include "ComputerVision/DeepLearning.h"
#include "Image/Image.h"
#include "Enums/SamplingDensity.h"

#include <memory>

namespace avl {
namespace DeepLearning {
namespace Common {
	struct ModelInfo
	{
		atl::Array<float> ValidationHistory;
	};

	struct Progress
	{
		struct Advancement
		{
			int Current;
			int Total;

			Advancement(); //do not use
			Advancement(int current, int total);
		};

		enum StageType
		{
			PREPARING,
			INITIALIZING,
			TRAINING,
			SAVING_MODEL,
			SOLUTION
		};

		StageType Stage;
		Advancement Phase;
		atl::Optional<Advancement> Step;
		atl::Optional<float> TrainingValue;
		atl::Optional<float> ValidationValue;
		bool Validation;

		Progress(
			StageType stage,
			Advancement&& phase,
			bool validation = false,
			atl::Optional<Advancement>&& step = atl::NIL,
			atl::Optional<float>&& trainingValue = atl::NIL,
			atl::Optional<float>&& validationValue = atl::NIL
		);
	};

	atl::String ToString(Progress::StageType stage);

	class TrainingEventsHandler
	{
	public:
		virtual void ReceivedExistingModelInfo(const ModelInfo& existingModelInfo);

		virtual bool ReceivedProgress(const Progress& progress);

		virtual void SavedModelAutomatically(bool savedModel);

		virtual bool SaveModel();

		virtual ~TrainingEventsHandler();
	};

	class ConstantSizePreprocessingConfig
	{
	public:
		static std::unique_ptr<ConstantSizePreprocessingConfig> Create(
			bool convertToGrayscale = false
		);

		virtual std::unique_ptr<ConstantSizePreprocessingConfig> Clone() const = 0;

		virtual void SetConvertToGrayscale(bool convertToGrayscale) = 0;
		virtual bool GetConvertToGrayscale() const = 0;

		virtual ~ConstantSizePreprocessingConfig() {}
	};

	class AllPreprocessingConfig
	{
	public:
		static std::unique_ptr<AllPreprocessingConfig> Create(
			bool convertToGrayscale = false,
			int downsample = 0
		);

		virtual std::unique_ptr<AllPreprocessingConfig> Clone() const = 0;

		virtual void SetConvertToGrayscale(bool convertToGrayscale) = 0;
		virtual bool GetConvertToGrayscale() const = 0;

		virtual void SetDownsample(int downsample) = 0;
		virtual int GetDownsample() const = 0;

		virtual ~AllPreprocessingConfig() {}
	};

	class ContextfreeAugmentationsConfig
	{
	public:
		static std::unique_ptr<ContextfreeAugmentationsConfig> Create(
			bool flipLeftRight = false,
			bool flipUpDown = false,
			int noise = 0,
			int luminance = 0
		);

		virtual std::unique_ptr<ContextfreeAugmentationsConfig> Clone() const = 0;

		virtual void SetFlipLeftRight(bool flip) = 0;
		virtual bool GetFlipLeftRight() const = 0;

		virtual void SetFlipUpDown(bool flip) = 0;
		virtual bool GetFlipUpDown() const = 0;

		virtual void SetNoise(int noise) = 0;
		virtual int GetNoise() const = 0;

		virtual void SetLuminance(int luminance) = 0;
		virtual int GetLuminance() const = 0;

		virtual ~ContextfreeAugmentationsConfig() {}
	};

	class AllAugmentationsConfig
	{
	public:
		static std::unique_ptr<AllAugmentationsConfig> Create(
			bool flipLeftRight = false,
			bool flipUpDown = false,
			int noise = 0,
			int luminance = 0,
			int rotationAngle = 0
		);

		virtual std::unique_ptr<AllAugmentationsConfig> Clone() const = 0;

		virtual void SetFlipLeftRight(bool flip) = 0;
		virtual bool GetFlipLeftRight() const = 0;

		virtual void SetFlipUpDown(bool flip) = 0;
		virtual bool GetFlipUpDown() const = 0;

		virtual void SetNoise(int noise) = 0;
		virtual int GetNoise() const = 0;

		virtual void SetLuminance(int luminance) = 0;
		virtual int GetLuminance() const = 0;

		virtual void SetRotationAngle(int rotationAngle) = 0;
		virtual int GetRotationAngle() const = 0;

		virtual ~AllAugmentationsConfig() {}
	};

	class AnomalyDetectionSample
	{
	public:
		static std::unique_ptr<AnomalyDetectionSample> Create(
			atl::File image,
			bool label
		);

		virtual std::unique_ptr<AnomalyDetectionSample> Clone() const = 0;

		virtual void SetImage(atl::File image) = 0;
		virtual const atl::File& GetImage() const = 0;

		virtual void SetLabel(bool label) = 0;
		virtual bool GetLabel() const = 0;

		virtual ~AnomalyDetectionSample() {}
	};

	class AnomalyDetectionTrainingEventsHandler : public TrainingEventsHandler
	{
	public:
		virtual void SolvedTrainingSample(const AnomalyDetectionSample& trainingSample, avl::Image reconstruction, avl::Image heatmap, float score);
	};
} //namespace Common

namespace AnomalyDetection_Global {
	typedef Common::ConstantSizePreprocessingConfig PreprocessingConfig;

	typedef Common::ContextfreeAugmentationsConfig AugmentationsConfig;

	class TrainingConfig
	{
	public:
		static std::unique_ptr<TrainingConfig> Create(
			atl::Directory modelLocation,
			int imageWidth,
			int imageHeight,
			atl::Optional<atl::File> roiCommon = atl::NIL,
			int networkDepth = 3,
			int iterationCount = 1000,
			std::unique_ptr<PreprocessingConfig> preprocessing = PreprocessingConfig::Create(),
			std::unique_ptr<AugmentationsConfig> augmentations = AugmentationsConfig::Create()
		);

		virtual std::unique_ptr<TrainingConfig> Clone() const = 0;

		virtual void SetPreprocessing(std::unique_ptr<PreprocessingConfig>) = 0;
		virtual PreprocessingConfig& GetPreprocessing() = 0;
		virtual const PreprocessingConfig& GetPreprocessing() const = 0;

		virtual void SetAugmentations(std::unique_ptr<AugmentationsConfig>) = 0;
		virtual AugmentationsConfig& GetAugmentations() = 0;
		virtual const AugmentationsConfig& GetAugmentations() const = 0;

		virtual void SetModelLocation(atl::Directory modelLocation) = 0;
		virtual const atl::Directory& GetModelLocation() const = 0;

		virtual void SetNetworkDepth(int networkDepth) = 0;
		virtual int GetNetworkDepth() const = 0;

		virtual void SetIterationCount(int iterationCount) = 0;
		virtual int GetIterationCount() const = 0;

		virtual void SetImageSize(int width, int height) = 0;
		virtual int GetImageWidth() const = 0;
		virtual int GetImageHeight() const = 0;

		virtual void SetRoiCommon(atl::Optional<atl::File>) = 0;
		virtual const atl::Optional<atl::File>& GetRoiCommon() const = 0;

		virtual ~TrainingConfig() {}
	};

	typedef Common::AnomalyDetectionSample Sample;

	atl::Array<std::unique_ptr<Sample>> CreateSamples(const atl::Directory& directory, bool label, const atl::String& mask = "*");

	typedef Common::AnomalyDetectionTrainingEventsHandler TrainingEventsHandler;

	bool Train(
		DeepLearningConnectionState& state,
		const atl::Array<atl::Array<std::unique_ptr<Sample>>>& trainingSamples,
		const TrainingConfig& config,
		TrainingEventsHandler& eventsHandler
	);

	inline bool Train(
		DeepLearningConnectionState& state,
		const atl::Array<atl::Array<std::unique_ptr<Sample>>>& trainingSamples,
		const TrainingConfig& config
	)
	{
		TrainingEventsHandler eventsHandler;
		return Train(state, trainingSamples, config, eventsHandler);
	}

	float GetWorstValidationValue();
	bool IsValidationBetter(float oldValidationValue, float newValidationValue);
	float FindBestValidation(const atl::Array<float>&);
} //namespace AnomalyDetection_Global

namespace AnomalyDetection_Local {
	typedef Common::AllPreprocessingConfig PreprocessingConfig;

	typedef Common::AllAugmentationsConfig AugmentationsConfig;

	class TrainingConfig
	{
	public:
		static std::unique_ptr<TrainingConfig> Create(
			atl::Directory modelLocation,
			int imageWidth,
			int imageHeight,
			SamplingDensity::Type samplingDensity = SamplingDensity::Medium,
			int featureSize = 24,
			atl::Optional<atl::File> roiCommon = atl::NIL,
			int networkDepth = 3,
			int iterationCount = 1000,
			std::unique_ptr<PreprocessingConfig> preprocessing = PreprocessingConfig::Create(),
			std::unique_ptr<AugmentationsConfig> augmentations = AugmentationsConfig::Create()
		);

		virtual std::unique_ptr<TrainingConfig> Clone() const = 0;

		virtual void SetPreprocessing(std::unique_ptr<PreprocessingConfig>) = 0;
		virtual PreprocessingConfig& GetPreprocessing() = 0;
		virtual const PreprocessingConfig& GetPreprocessing() const = 0;

		virtual void SetAugmentations(std::unique_ptr<AugmentationsConfig>) = 0;
		virtual AugmentationsConfig& GetAugmentations() = 0;
		virtual const AugmentationsConfig& GetAugmentations() const = 0;

		virtual void SetModelLocation(atl::Directory modelLocation) = 0;
		virtual const atl::Directory& GetModelLocation() const = 0;

		virtual void SetNetworkDepth(int networkDepth) = 0;
		virtual int GetNetworkDepth() const = 0;

		virtual void SetIterationCount(int iterationCount) = 0;
		virtual int GetIterationCount() const = 0;

		virtual void SetFeatureSize(int featureSize) = 0;
		virtual int GetFeatureSize() const = 0;

		virtual void SetImageSize(int width, int height) = 0;
		virtual int GetImageWidth() const = 0;
		virtual int GetImageHeight() const = 0;

		virtual void SetRoiCommon(atl::Optional<atl::File>) = 0;
		virtual const atl::Optional<atl::File>& GetRoiCommon() const = 0;

		virtual void SetSamplingDensity(SamplingDensity::Type samplingDensity) = 0;
		virtual SamplingDensity::Type GetSamplingDensity() const = 0;

		virtual ~TrainingConfig() {}
	};

	typedef Common::AnomalyDetectionSample Sample;

	atl::Array<std::unique_ptr<Sample>> CreateSamples(const atl::Directory& directory, bool label, const atl::String& mask = "*");

	typedef Common::AnomalyDetectionTrainingEventsHandler TrainingEventsHandler;

	bool Train(
		DeepLearningConnectionState& state,
		const atl::Array<atl::Array<std::unique_ptr<Sample>>>& trainingSamples,
		const TrainingConfig& config,
		TrainingEventsHandler& eventsHandler
	);

	inline bool Train(
		DeepLearningConnectionState& state,
		const atl::Array<atl::Array<std::unique_ptr<Sample>>>& trainingSamples,
		const TrainingConfig& config
	)
	{
		TrainingEventsHandler eventsHandler;
		return Train(state, trainingSamples, config, eventsHandler);
	}

	float GetWorstValidationValue();
	bool IsValidationBetter(float oldValidationValue, float newValidationValue);
	float FindBestValidation(const atl::Array<float>&);
} //namespace AnomalyDetection_Local

namespace AnomalyDetection2 {
	typedef Common::AllPreprocessingConfig PreprocessingConfig;

	typedef Common::AllAugmentationsConfig AugmentationsConfig;

	class TrainingConfig
	{
	public:
		static std::unique_ptr<TrainingConfig> Create(
			atl::Directory modelLocation,
			int imageWidth,
			int imageHeight,
			SamplingDensity::Type samplingDensity = SamplingDensity::Medium,
			int featureSize = 24,
			atl::Optional<atl::File> roiCommon = atl::NIL,
			int networkDepth = 3,
			std::unique_ptr<PreprocessingConfig> preprocessing = PreprocessingConfig::Create(),
			std::unique_ptr<AugmentationsConfig> augmentations = AugmentationsConfig::Create()
		);

		virtual std::unique_ptr<TrainingConfig> Clone() const = 0;

		virtual void SetPreprocessing(std::unique_ptr<PreprocessingConfig>) = 0;
		virtual PreprocessingConfig& GetPreprocessing() = 0;
		virtual const PreprocessingConfig& GetPreprocessing() const = 0;

		virtual void SetAugmentations(std::unique_ptr<AugmentationsConfig>) = 0;
		virtual AugmentationsConfig& GetAugmentations() = 0;
		virtual const AugmentationsConfig& GetAugmentations() const = 0;

		virtual void SetModelLocation(atl::Directory modelLocation) = 0;
		virtual const atl::Directory& GetModelLocation() const = 0;

		virtual void SetNetworkDepth(int networkDepth) = 0;
		virtual int GetNetworkDepth() const = 0;

		virtual void SetFeatureSize(int featureSize) = 0;
		virtual int GetFeatureSize() const = 0;

		virtual void SetImageSize(int width, int height) = 0;
		virtual int GetImageWidth() const = 0;
		virtual int GetImageHeight() const = 0;

		virtual void SetRoiCommon(atl::Optional<atl::File>) = 0;
		virtual const atl::Optional<atl::File>& GetRoiCommon() const = 0;

		virtual void SetSamplingDensity(SamplingDensity::Type samplingDensity) = 0;
		virtual SamplingDensity::Type GetSamplingDensity() const = 0;

		virtual ~TrainingConfig() {}
	};

	typedef Common::AnomalyDetectionSample Sample;

	atl::Array<std::unique_ptr<Sample>> CreateSamples(const atl::Directory& directory, bool label, const atl::String& mask = "*");

	class TrainingEventsHandler : public Common::TrainingEventsHandler
	{
	public:
		virtual void SolvedTrainingSample(const Sample& trainingSample, avl::Image heatmap, float score);
	};

	bool Train(
		DeepLearningConnectionState& state,
		const atl::Array<atl::Array<std::unique_ptr<Sample>>>& trainingSamples,
		const TrainingConfig& config,
		TrainingEventsHandler& eventsHandler
	);

	inline bool Train(
		DeepLearningConnectionState& state,
		const atl::Array<atl::Array<std::unique_ptr<Sample>>>& trainingSamples,
		const TrainingConfig& config
	)
	{
		TrainingEventsHandler eventsHandler;
		return Train(state, trainingSamples, config, eventsHandler);
	}
} //namespace AnomalyDetection2

namespace FeatureDetection {
	typedef Common::AllPreprocessingConfig PreprocessingConfig;

	typedef Common::AllAugmentationsConfig AugmentationsConfig;

	class TrainingConfig
	{
	public:
		static std::unique_ptr<TrainingConfig> Create(
			atl::Directory modelLocation,
			int featureSize = 48,
			int networkDepth = 3,
			int iterationCount = 1000,
			std::unique_ptr<PreprocessingConfig> preprocessing = PreprocessingConfig::Create(),
			std::unique_ptr<AugmentationsConfig> augmentations = AugmentationsConfig::Create()
		);

		virtual std::unique_ptr<TrainingConfig> Clone() const = 0;

		virtual void SetPreprocessing(std::unique_ptr<PreprocessingConfig>) = 0;
		virtual PreprocessingConfig& GetPreprocessing() = 0;
		virtual const PreprocessingConfig& GetPreprocessing() const = 0;

		virtual void SetAugmentations(std::unique_ptr<AugmentationsConfig>) = 0;
		virtual AugmentationsConfig& GetAugmentations() = 0;
		virtual const AugmentationsConfig& GetAugmentations() const = 0;

		virtual void SetModelLocation(atl::Directory modelLocation) = 0;
		virtual const atl::Directory& GetModelLocation() const = 0;

		virtual void SetNetworkDepth(int networkDepth) = 0;
		virtual int GetNetworkDepth() const = 0;

		virtual void SetIterationCount(int iterationCount) = 0;
		virtual int GetIterationCount() const = 0;

		virtual void SetFeatureSize(int featureSize) = 0;
		virtual int GetFeatureSize() const = 0;

		virtual ~TrainingConfig() {}
	};

	class Sample
	{
	public:
		static std::unique_ptr<Sample> Create(
			atl::File image,
			atl::Array<atl::Optional<atl::File>> labels = atl::Array<atl::Optional<atl::File>>(),
			atl::Optional<atl::File> roi = atl::NIL
		);

		virtual std::unique_ptr<Sample> Clone() const = 0;

		virtual void SetImage(atl::File image) = 0;
		virtual const atl::File& GetImage() const = 0;

		virtual void AddLabel(atl::Optional<atl::File>) = 0;
		virtual void SetLabel(atl::Optional<atl::File>, int index) = 0;
		virtual void SetLabels(atl::Array<atl::Optional<atl::File>>) = 0;

		virtual const atl::Array<atl::Optional<atl::File>>& GetLabels() const = 0;

		virtual void SetRoi(atl::Optional<atl::File> roi) = 0;
		virtual const atl::Optional<atl::File>& GetRoi() const = 0;

		virtual ~Sample() {}
	};

	atl::Array<std::unique_ptr<Sample>> CreateSamples(
		const atl::Directory& samplesDirectory,
		const atl::Array<atl::Directory>& labelDirectories,
		const atl::Optional<atl::Directory>& roiDirectory = atl::NIL,
		const atl::String& mask = "*"
	);

	class TrainingEventsHandler : public Common::TrainingEventsHandler
	{
	public:
		virtual void SolvedTrainingSample(const Sample& trainingSample, atl::Array<avl::Image> heatmaps);
	};

	bool Train(
		DeepLearningConnectionState& state,
		const atl::Array<std::unique_ptr<Sample>>& trainingSamples,
		const TrainingConfig& config,
		TrainingEventsHandler& eventsHandler
	);

	inline bool Train(
		DeepLearningConnectionState& state,
		const atl::Array<std::unique_ptr<Sample>>& trainingSamples,
		const TrainingConfig& config
	)
	{
		TrainingEventsHandler eventsHandler;
		return Train(state, trainingSamples, config, eventsHandler);
	}

	void SolveTrainingSamples(
		DeepLearningConnectionState& state,
		const atl::Array<std::unique_ptr<Sample>>& trainingSamples,
		const TrainingConfig& config,
		TrainingEventsHandler& eventsHandler
	);

	float GetWorstValidationValue();
	bool IsValidationBetter(float oldValidationValue, float newValidationValue);
	float FindBestValidation(const atl::Array<float>&);
} //namespace FeatureDetection

namespace ObjectClassification {
	typedef Common::ConstantSizePreprocessingConfig PreprocessingConfig;

	typedef Common::ContextfreeAugmentationsConfig AugmentationsConfig;

	class TrainingConfig
	{
	public:
		static std::unique_ptr<TrainingConfig> Create(
			atl::Directory modelLocation,
			int networkDepth = 3,
			int iterationCount = 1000,
			std::unique_ptr<PreprocessingConfig> preprocessing = PreprocessingConfig::Create(),
			std::unique_ptr<AugmentationsConfig> augmentations = AugmentationsConfig::Create()
		);

		virtual std::unique_ptr<TrainingConfig> Clone() const = 0;

		virtual void SetPreprocessing(std::unique_ptr<PreprocessingConfig>) = 0;
		virtual PreprocessingConfig& GetPreprocessing() = 0;
		virtual const PreprocessingConfig& GetPreprocessing() const = 0;

		virtual void SetAugmentations(std::unique_ptr<AugmentationsConfig>) = 0;
		virtual AugmentationsConfig& GetAugmentations() = 0;
		virtual const AugmentationsConfig& GetAugmentations() const = 0;

		virtual void SetModelLocation(atl::Directory modelLocation) = 0;
		virtual const atl::Directory& GetModelLocation() const = 0;

		virtual void SetNetworkDepth(int networkDepth) = 0;
		virtual int GetNetworkDepth() const = 0;

		virtual void SetIterationCount(int iterationCount) = 0;
		virtual int GetIterationCount() const = 0;

		virtual ~TrainingConfig() {};
	};

	class Sample
	{
	public:
		static std::unique_ptr<Sample> Create(
			atl::File image,
			atl::String label,
			atl::Optional<atl::File> roi = atl::NIL
		);

		virtual std::unique_ptr<Sample> Clone() const = 0;

		virtual void SetImage(atl::File image) = 0;
		virtual const atl::File& GetImage() const = 0;

		virtual void SetLabel(atl::String) = 0;
		virtual const atl::String& GetLabel() const = 0;

		virtual void SetRoi(atl::Optional<atl::File> roi) = 0;
		virtual const atl::Optional<atl::File>& GetRoi() const = 0;

		virtual ~Sample() {}
	};

	atl::Array<std::unique_ptr<Sample>> CreateSamples(
		const atl::Directory& samplesDirectory,
		const atl::String& label,
		const atl::Optional<atl::Directory>& roiDirectory = atl::NIL,
		const atl::String& mask = "*"
	);

	class TrainingEventsHandler : public Common::TrainingEventsHandler
	{
	public:
		virtual void SolvedTrainingSample(const Sample& trainingSample, atl::Array<ClassConfidence> confidences, int bestClassificationIndex);
	};

	bool Train(
		DeepLearningConnectionState& state,
		const atl::Array<atl::Array<std::unique_ptr<Sample>>>& trainingSamples,
		const TrainingConfig& config,
		TrainingEventsHandler& eventsHandler
	);

	inline bool Train(
		DeepLearningConnectionState& state,
		const atl::Array<atl::Array<std::unique_ptr<Sample>>>& trainingSamples,
		const TrainingConfig& config
	)
	{
		TrainingEventsHandler eventsHandler;
		return Train(state, trainingSamples, config, eventsHandler);
	}

	void SolveTrainingSamples(
		DeepLearningConnectionState& state,
		const atl::Array<atl::Array<std::unique_ptr<Sample>>>& trainingSamples,
		const TrainingConfig& config,
		TrainingEventsHandler& eventsHandler
	);

	float GetWorstValidationValue();
	bool IsValidationBetter(float oldValidationValue, float newValidationValue);
	float FindBestValidation(const atl::Array<float>&);
} //namespace ObjectClassification

namespace InstanceSegmentation
{
	typedef Common::ConstantSizePreprocessingConfig PreprocessingConfig;

	typedef Common::AllAugmentationsConfig AugmentationsConfig;

	class TrainingConfig
	{
	  public:
		static std::unique_ptr<TrainingConfig> Create(
			atl::Directory modelLocation,
			int networkDepth = 3,
			int iterationCount = 50,
			std::unique_ptr<PreprocessingConfig> preprocessing = PreprocessingConfig::Create(),
			std::unique_ptr<AugmentationsConfig> augmentations = AugmentationsConfig::Create());

		virtual std::unique_ptr<TrainingConfig> Clone() const = 0;

		virtual void SetPreprocessing(std::unique_ptr<PreprocessingConfig>) = 0;
		virtual PreprocessingConfig& GetPreprocessing() = 0;
		virtual const PreprocessingConfig& GetPreprocessing() const = 0;

		virtual void SetAugmentations(std::unique_ptr<AugmentationsConfig>) = 0;
		virtual AugmentationsConfig& GetAugmentations() = 0;
		virtual const AugmentationsConfig& GetAugmentations() const = 0;

		virtual void SetModelLocation(atl::Directory modelLocation) = 0;
		virtual const atl::Directory& GetModelLocation() const = 0;

		virtual void SetNetworkDepth(int networkDepth) = 0;
		virtual int GetNetworkDepth() const = 0;

		virtual void SetIterationCount(int iterationCount) = 0;
		virtual int GetIterationCount() const = 0;

		virtual ~TrainingConfig(){};
	};

	class Sample
	{
	  public:
		static std::unique_ptr<Sample> Create(
			atl::File image,
			atl::Array<atl::Array<atl::File>> instances,
			atl::Optional<atl::File> roi = atl::NIL);

		virtual std::unique_ptr<Sample> Clone() const = 0;

		virtual void SetImage(atl::File image) = 0;
		virtual const atl::File& GetImage() const = 0;

		virtual atl::Array<atl::Array<atl::File>>& GetInstances() = 0;
		virtual const atl::Array<atl::Array<atl::File>>& GetInstances() const = 0;

		virtual void SetRoi(atl::Optional<atl::File> roi) = 0;
		virtual const atl::Optional<atl::File>& GetRoi() const = 0;

		virtual ~Sample() {}
	};

	atl::Array<std::unique_ptr<Sample>> CreateSamples(
		const atl::Directory& samplesDirectory,
		const atl::Array<atl::Directory>& instanceDirectories,
		const atl::Optional<atl::Directory>& roiDirectory = atl::NIL,
		const atl::String& mask = "*");

	class TrainingEventsHandler : public Common::TrainingEventsHandler
	{
	  public:
		virtual void SolvedTrainingSample(const Sample& trainingSample,
			atl::Array<avl::Region> masks, atl::Array<avl::Box> boundingBoxes, atl::Array<float> scores, atl::Array<atl::String> classNames, atl::Array<int> classIds);
	};

	bool Train(
		DeepLearningConnectionState& state,
		const atl::Array<std::unique_ptr<Sample>>& trainingSamples,
		const TrainingConfig& config,
		TrainingEventsHandler& eventsHandler);

	inline bool Train(
		DeepLearningConnectionState& state,
		const atl::Array<std::unique_ptr<Sample>>& trainingSamples,
		const TrainingConfig& config)
	{
		TrainingEventsHandler eventsHandler;
		return Train(state, trainingSamples, config, eventsHandler);
	}

	void SolveTrainingSamples(
		DeepLearningConnectionState& state,
		const atl::Array<std::unique_ptr<Sample>>& trainingSamples,
		const TrainingConfig& config,
		atl::Optional<float> minDetectionScore,
		atl::Optional<int> maxObjectsCount,
		TrainingEventsHandler& eventsHandler);

	float GetWorstValidationValue();
	bool IsValidationBetter(float oldValidationValue, float newValidationValue);
	float FindBestValidation(const atl::Array<float>&);
} //namespace InstanceSegmentation
} //namespace DeepLearning
} //namespace avl
