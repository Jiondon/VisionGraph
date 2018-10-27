//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef IO_BASE_STATE_H
#define IO_BASE_STATE_H

#include <type_traits>
#include <ATL/Error.h>
#include <ATL/Optional.h>
#include <AVLCommon/CancellationTypes.h>

namespace avl
{
	template<class C>
	struct IoBaseState
	{
		C* interface;

		IoBaseState()
			:interface(nullptr)
		{}

		~IoBaseState()
		{
			if (interface)
				delete interface;
		}

		C* operator->() const
		{
			return interface;
		}

	private:
		IoBaseState(const IoBaseState&);
		IoBaseState& operator=(const IoBaseState&);
	};

	// To use KitBaseState, just include this header as PUBLIC,
	// then typedef KitBaseState<YourDeviceInterface> Your_State
	// then typedef YourDeviceId_or_address_Type DeviceIdType in the YourDeviceInterface class/struct
	// and be sure your interface has BindToDevice(const Optional<DeviceIdType>&) and SetCancellationObject methods defined
	// scalar ids will throw when changed on rebind, non scalars will ignore changes after BindToDevice
	// Interfaces with missing DeviceIdType will just not support BindToDevice
	template<class C, typename T = void>
	struct KitBaseState : public IoBaseState<C>
	{};

	typedef ICancellationProvider* (*GlobalCancellationProviderGetter)();

	template<class C>
	struct KitBaseState <C, typename std::enable_if<std::is_scalar<typename C::DeviceIdType>::value>::type> : public IoBaseState<C>
	{
		KitBaseState()
			: isConnected(false)
		{}

		void BindToDevice(const atl::Optional<typename C::DeviceIdType>& _dev, GlobalCancellationProviderGetter _icp)
		{
			if (!isConnected)
			{
				dev = _dev;
				this->interface->BindToDevice(dev);
				isConnected = true;
				if (_icp)
					this->interface->SetCancellationObject(_icp());
			}
			else
			{
				if (dev != _dev)
					throw atl::DomainError("It is not allowed to change device id in consecutive iterations.");
			}
		}

	private:
		atl::Optional<typename C::DeviceIdType> dev;
		bool isConnected;
	};

	template<class C>
	struct KitBaseState <C, typename std::enable_if<!std::is_scalar<typename C::DeviceIdType>::value>::type> : public IoBaseState<C>
	{
		KitBaseState()
			: isConnected(false)
		{}

		void BindToDevice(const atl::Optional<typename C::DeviceIdType>& _dev, GlobalCancellationProviderGetter _icp)
		{
			if (!isConnected)
			{
				dev = _dev;
				this->interface->BindToDevice(dev);
				isConnected = true;
				if(_icp)
					this->interface->SetCancellationObject(_icp());
			}
		}

	private:
		atl::Optional<typename C::DeviceIdType> dev;
		bool isConnected;
	};
}

#endif
