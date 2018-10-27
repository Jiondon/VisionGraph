//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_FTP_H
#define AVL_FTP_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlString.h"
#include "ATL/Optional.h"
#include "Enums/ImageFileFormat.h"
#include "Image/Image.h"

namespace avl
{


	/// <summary>Sends a file to a remote server using FTP (File Transfer Protocol).</summary>
	/// <param name="inFilePath">Path to a file stored on the local drive.</param>
	/// <param name="inHostName">URL address of the remote server. Default value: \"ftp://\".</param>
	/// <param name="inDestinationFileName">Path where a file should be saved on a remote server.</param>
	/// <param name="inUsername">User name needed to log in. Default value: atl::NIL.</param>
	/// <param name="inPassword">Password associated with a user name. Default value: atl::NIL.</param>
	/// <param name="inUsePassiveMode">Protocol communication mode. May be necessary when using a firewall.</param>
	AVL_FUNCTION void Ftp_SendFile
	(
		const atl::File&					inFilePath,				
		const atl::String&					inHostName,				
		const atl::String&					inDestinationFileName,	
		atl::Optional<const atl::String&>	inUsername,				
		atl::Optional<const atl::String&>	inPassword,				
		bool								inUsePassiveMode		
	)
	THROW_AVL_ERRORS;

	/// <summary>Sends a string to a remote serve using FTP (File Transfer Protocol).</summary>
	/// <param name="inText">Text to send.</param>
	/// <param name="inHostName">URL address of the remote server. Default value: \"ftp://\".</param>
	/// <param name="inDestinationFileName">Path where a text file should be saved on a remote server.</param>
	/// <param name="inUsername">User name needed to log in. Default value: atl::NIL.</param>
	/// <param name="inPassword">Password associated with a user name. Default value: atl::NIL.</param>
	/// <param name="inUsePassiveMode">Protocol communication mode. May be necessary when using a firewall.</param>
	AVL_FUNCTION void Ftp_SendString
	(
		const atl::String&					inText,					
		const atl::String&					inHostName,				
		const atl::String&					inDestinationFileName,	
		atl::Optional<const atl::String&>	inUsername,				
		atl::Optional<const atl::String&>	inPassword,				
		bool								inUsePassiveMode		
	)
	THROW_AVL_ERRORS;

	/// <summary>Sends an image to a remote server using the FTP (File Transfer Protocol)</summary>
	/// <param name="inImage">Image to send.</param>
	/// <param name="inImageFileFormat">If Nil the format will be chosen on the basis of extension. Default value: atl::NIL.</param>
	/// <param name="inHostName">URL address of the remote server. Default value: \"ftp://\".</param>
	/// <param name="inDestinationFileName">Path where an image file should be saved on a remote server.</param>
	/// <param name="inUsername">User name needed to log in. Default value: atl::NIL.</param>
	/// <param name="inPassword">Password associated with a user name. Default value: atl::NIL.</param>
	/// <param name="inUsePassiveMode">Protocol communication mode. May be necessary when using a firewall.</param>
	AVL_FUNCTION void Ftp_SendImage
	(
		const avl::Image&							inImage,					
		atl::Optional<avl::ImageFileFormat::Type>	inImageFileFormat,			
		const atl::String&							inHostName,					
		const atl::String&							inDestinationFileName,		
		atl::Optional<const atl::String&>			inUsername,					
		atl::Optional<const atl::String&>			inPassword,					
		bool										inUsePassiveMode			
	)
	THROW_AVL_ERRORS;

	/// <summary>Downloads a file from a remote server using FTP (File Transfer Protocol).</summary>
	/// <param name="inFilePath">Location of the file on a remote server.</param>
	/// <param name="inHostName">URL address of the remote server. Default value: \"ftp://\".</param>
	/// <param name="inFtpFilePath">Location of the file on a remote server.</param>
	/// <param name="inUsername">User name needed to log in. Default value: atl::NIL.</param>
	/// <param name="inPassword">Password associated with a user name. Default value: atl::NIL.</param>
	/// <param name="inUsePassiveMode">Protocol communication mode. May be necessary when using a firewall.</param>
	AVL_FUNCTION void Ftp_ReceiveFile
	(
		const atl::File&					inFilePath,			
		const atl::String&					inHostName,			
		const atl::String&					inFtpFilePath,		
		atl::Optional<const atl::String&>	inUsername,			
		atl::Optional<const atl::String&>	inPassword,			
		bool								inUsePassiveMode	
	)
	THROW_AVL_ERRORS;

	/// <summary>Downloads a text string from a remote server using FTP (File Transfer Protocol).</summary>
	/// <param name="inHostName">URL address of the remote server. Default value: \"ftp://\".</param>
	/// <param name="inFtpFilePath">Location of the file on a remote server.</param>
	/// <param name="inUsername">User name needed to log in. Default value: atl::NIL.</param>
	/// <param name="inPassword">Password associated with a user name. Default value: atl::NIL.</param>
	/// <param name="inUsePassiveMode">Protocol communication mode. May be necessary when using a firewall.</param>
	/// <param name="outText">Text read from a remote server.</param>
	AVL_FUNCTION void Ftp_ReceiveString
	(
		const atl::String&					inHostName,			
		const atl::String&					inFtpFilePath,		
		atl::Optional<const atl::String&>	inUsername,			
		atl::Optional<const atl::String&>	inPassword,			
		bool								inUsePassiveMode,	
		atl::String&						outText				
	)
	THROW_AVL_ERRORS;

	/// <summary>Downloads an image from a remote server using FTP (File Transfer Protocol).</summary>
	/// <param name="inHostName">URL address of the remote server. Default value: \"ftp://\".</param>
	/// <param name="inFtpFilePath">Location of the file on a remote server.</param>
	/// <param name="inUsername">User name needed to log in. Default value: atl::NIL.</param>
	/// <param name="inPassword">Password associated with a user name. Default value: atl::NIL.</param>
	/// <param name="inUsePassiveMode">Protocol communication mode. May be necessary when using a firewall.</param>
	/// <param name="inLoadAlphaChannel">Whether to load the alpha channel (if exists) as an additional image channel.</param>
	/// <param name="outImage">Image downloaded from the remote server.</param>
	AVL_FUNCTION void Ftp_ReceiveImage
	(
		const atl::String&					inHostName,			
		const atl::String&					inFtpFilePath,		
		atl::Optional<const atl::String&>	inUsername,			
		atl::Optional<const atl::String&>	inPassword,			
		bool								inUsePassiveMode,	
		bool								inLoadAlphaChannel, 
		avl::Image&							outImage			
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_FTP_H

