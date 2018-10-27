//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_XML_H
#define AVL_XML_H

#include "AVLCommon/Config.h"
#include "AVLCommon/BaseState.h"
#include "ATL/Optional.h"
#include "ATL/Dummy.h"
#include "ATL/AtlString.h"
#include "ATL/Array.hxx"

namespace avl
{


	class XmlNode;

	namespace pImpl_helpers
	{
		/* For internal use only */
		AVL_FUNCTION bool XmlNode_Validate(const XmlNode&);
		AVL_FUNCTION void XmlNode_FromString(const atl::String&, XmlNode&);
		AVL_FUNCTION void XmlNode_Create(const atl::String&, const atl::String&, XmlNode&);

		AVL_FUNCTION void XmlNode_AddNode(const XmlNode&, XmlNode&);

		AVL_FUNCTION void XmlNode_GetName(const XmlNode&, atl::String&);
		AVL_FUNCTION void XmlNode_GetText(const XmlNode&, atl::String&);

		AVL_FUNCTION void XmlNode_GetChildren(const XmlNode&, atl::Array<XmlNode>&);
	}

	class XmlNode
	{
		public:
			atl::String Value;

			XmlNode():Value(""){}

			XmlNode(const XmlNode& inXmlNode)
			{
				Value = inXmlNode.Value;
			}

			explicit XmlNode(const atl::String& inString)
			{
				pImpl_helpers::XmlNode_FromString(inString, *this);
			}

			XmlNode(const atl::String& inName, const atl::String& inTextValue)
			{
				pImpl_helpers::XmlNode_Create(inName, inTextValue, *this);
			}

			XmlNode& operator=(const XmlNode& inXmlNode)
			{
				if (inXmlNode.Value == Value)
					return *this;

				Value = inXmlNode.Value;
				return *this;
			}

			bool operator == (const XmlNode& rhs) const
			{
				return Value == rhs.Value;
			}
		
			bool operator != (const XmlNode& rhs) const
			{
				return !(operator==(rhs));
			}

			const atl::String Name() const
			{
				atl::String name;
				pImpl_helpers::XmlNode_GetName(*this, name);
				return name;
			}

			const atl::String Text() const
			{
				atl::String text;
				pImpl_helpers::XmlNode_GetText(*this, text);
				return text;
			}

			void AddChildNode(const XmlNode& node)
			{
				pImpl_helpers::XmlNode_AddNode(node, *this);
			}

			void AddChildNode(atl::String name, atl::String text)
			{
				XmlNode node(name, text);
				pImpl_helpers::XmlNode_AddNode(node, *this);
			}

			void AddChildrenNodes(const atl::Array<XmlNode>& nodes)
			{
				for(int i = 0; i < nodes.Size(); ++i)
					pImpl_helpers::XmlNode_AddNode(nodes[i], *this);
			}

			const atl::Array<XmlNode> GetChildrenNodes()
			{
				atl::Array<XmlNode> children;
				pImpl_helpers::XmlNode_GetChildren(*this, children);
				return children;
			}

			bool Valid() const
			{
				return pImpl_helpers::XmlNode_Validate(*this);
			}
	};


	/// <summary>Loads an XML tree from the file.</summary>
	/// <param name="inFile">Path to an XML file.</param>
	/// <param name="outNode">Result XML DOM object.</param>
	AVL_FUNCTION void Xml_LoadFile
	(
		const atl::File&			inFile,		
		avl::XmlNode&				outNode		
	)
	THROW_AVL_ERRORS;

	/// <summary>Saves an XML DOM tree to the file.</summary>
	/// <param name="inFile">Path to the destination file.</param>
	/// <param name="inNode">XML tree to save.</param>
	AVL_FUNCTION void Xml_SaveFile
	(
		const atl::File&			inFile,		
		const avl::XmlNode&			inNode		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets a node child.</summary>
	/// <param name="inNode">Source node.</param>
	/// <param name="inIndex">Child node index.</param>
	/// <param name="outChild">Child node of the inNode.</param>
	AVL_FUNCTION void Xml_GetChildNode
	(
		const avl::XmlNode&			inNode,			
		const int&					inIndex,		
		avl::XmlNode&				outChild		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets a node attribute value as String.</summary>
	/// <param name="inNode">Source node.</param>
	/// <param name="inName">Attribute name.</param>
	/// <param name="inDefault">Value if attribute was not found. Default value: atl::NIL.</param>
	/// <param name="outValue">Attribute value.</param>
	AVL_FUNCTION void Xml_GetStringAttribute
	(
		const avl::XmlNode&					inNode,			
		const atl::String&					inName,			
		const atl::Optional<atl::String>&	inDefault,		
		atl::String&						outValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets a node attribute value as Bool.</summary>
	/// <param name="inNode">Source node.</param>
	/// <param name="inName">Attribute name.</param>
	/// <param name="inDefault">Value if attribute was not found. Default value: atl::NIL.</param>
	/// <param name="outValue">Attribute value.</param>
	AVL_FUNCTION void Xml_GetBoolAttribute
	(
		const avl::XmlNode&			inNode,			
		const atl::String&			inName,			
		const atl::Optional<bool>&	inDefault,		
		bool&						outValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets a node attribute value as Integer.</summary>
	/// <param name="inNode">Source node.</param>
	/// <param name="inName">Attribute name.</param>
	/// <param name="inDefault">Value if attribute was not found. Default value: atl::NIL.</param>
	/// <param name="outValue">Attribute value.</param>
	AVL_FUNCTION void Xml_GetIntegerAttribute
	(
		const avl::XmlNode&			inNode,			
		const atl::String&			inName,			
		const atl::Optional<int>&	inDefault,		
		int&						outValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets a node attribute value as Real.</summary>
	/// <param name="inNode">Source node.</param>
	/// <param name="inName">Attribute name.</param>
	/// <param name="inDefault">Value if attribute was not found. Default value: atl::NIL.</param>
	/// <param name="outValue">Attribute value.</param>
	AVL_FUNCTION void Xml_GetRealAttribute
	(
		const avl::XmlNode&				inNode,			
		const atl::String&				inName,			
		const atl::Optional<float>&	inDefault,		
		float&						outValue		
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets information from the XmlNode object.</summary>
	/// <param name="outChildren">Children nodes of the inNode.</param>
	/// <param name="outAttributeNames">List of attributes names.</param>
	/// <param name="outAttributeValues">List of attributes values.</param>
	/// <param name="outName">Node name.</param>
	/// <param name="outText">Text value if node is a text node.</param>
	AVL_FUNCTION void AccessXmlNode
	(
		const avl::XmlNode&			inNode,	
		atl::Array<avl::XmlNode>&	outChildren,		
		atl::Array<atl::String>&	outAttributeNames,	
		atl::Array<atl::String>&	outAttributeValues, 
		atl::String&				outName,			
		atl::String&				outText				
	)
	THROW_AVL_ERRORS;

	/// <summary>Gets the text from the selected node.</summary>
	/// <param name="outText">Text value if node is a text node.</param>
	AVL_FUNCTION void Xml_GetNodeText
	(
		const avl::XmlNode&			inNode,	
		atl::String&				outText				
	)
	THROW_AVL_ERRORS;

	/// <summary>Converts an XML tree to the string.</summary>
	/// <param name="inNode">XmlNode to be converted.</param>
	AVL_FUNCTION void XmlNodeToString
	(
		const avl::XmlNode&			inNode,		
		atl::String&				outText		
	)
	THROW_AVL_ERRORS;

	/// <summary>Parses text as an XML tree.</summary>
	/// <param name="inText">Text to be parsed as an XML tree.</param>
	AVL_FUNCTION void StringToXmlNode
	(
		const atl::String&			inText,		
		avl::XmlNode&				outNode		
	)
	THROW_AVL_ERRORS;

	/// <summary>Appends new children nodes to the XML node.</summary>
	/// <param name="inParent">Parent XML node to which new nodes will be added.</param>
	/// <param name="inChild1">Node to be added.</param>
	/// <param name="inChild2">Node to be added. Default value: atl::NIL.</param>
	/// <param name="inChild3">Node to be added. Default value: atl::NIL.</param>
	/// <param name="inChild4">Node to be added. Default value: atl::NIL.</param>
	/// <param name="inChild5">Node to be added. Default value: atl::NIL.</param>
	/// <param name="inChild6">Node to be added. Default value: atl::NIL.</param>
	/// <param name="inChild7">Node to be added. Default value: atl::NIL.</param>
	/// <param name="inChild8">Node to be added. Default value: atl::NIL.</param>
	/// <param name="outNode">New node with added nodes.</param>
	AVL_FUNCTION void Xml_AddChildNodes
	(
		const avl::XmlNode&							inParent,		
		const avl::XmlNode&							inChild1,		
		const atl::Optional<avl::XmlNode>&			inChild2,		
		const atl::Optional<avl::XmlNode>&			inChild3,		
		const atl::Optional<avl::XmlNode>&			inChild4,		
		const atl::Optional<avl::XmlNode>&			inChild5,		
		const atl::Optional<avl::XmlNode>&			inChild6,		
		const atl::Optional<avl::XmlNode>&			inChild7,		
		const atl::Optional<avl::XmlNode>&			inChild8,		
		avl::XmlNode&								outNode			
	)
	THROW_AVL_ERRORS;

	/// <summary>Appends new children nodes to the XML node.</summary>
	/// <param name="inParent">Parent XML node to which new nodes will be added.</param>
	/// <param name="inChildren">Nodes to be added.</param>
	/// <param name="outNode">New node with added nodes.</param>
	AVL_FUNCTION void Xml_AddChildNodes_OfArray
	(
		const avl::XmlNode&				inParent,		
		const atl::Array<avl::XmlNode>&	inChildren,		
		avl::XmlNode&					outNode			
	)
	THROW_AVL_ERRORS;

	/// <summary>Appends new attributes to the node.</summary>
	/// <param name="inNode">Node to which new attributes will be added.</param>
	/// <param name="inNames">Attributes names.</param>
	/// <param name="inValues">Attributes values.</param>
	AVL_FUNCTION void Xml_AppendAttributes
	(
		const avl::XmlNode&						inNode,		
		const atl::Array<atl::String>&			inNames,	
		const atl::Array<atl::String>&			inValues,	
		avl::XmlNode&							outNode	
	)
	THROW_AVL_ERRORS;

	/// <summary>Creates a new XmlNode.</summary>
	/// <param name="inName">Node name.</param>
	/// <param name="inText">Text value of XmlNode.</param>
	/// <param name="inAttributeNames">Attributes names.</param>
	/// <param name="inAttributeValues">Attributes values.</param>
	AVL_FUNCTION void Xml_CreateNode
	(
		const atl::String&					inName,				
		const atl::String&					inText,				
		const atl::Array<atl::String>&		inAttributeNames,	
		const atl::Array<atl::String>&		inAttributeValues,	
		avl::XmlNode&						outNode	
	)
	THROW_AVL_ERRORS;

	/// <summary>Selects nodes from the XML tree using XPath request.</summary>
	/// <param name="inNode">Source node.</param>
	/// <param name="inXPath">XPath criteria.</param>
	/// <param name="outNodes">Found nodes.</param>
	AVL_FUNCTION void Xml_SelectMultipleNodes
	(
		const avl::XmlNode&				inNode,			
		const atl::String&				inXPath,		
		atl::Array<avl::XmlNode>&		outNodes		
	)
	THROW_AVL_ERRORS;

	/// <summary>Selects a node from the XML tree using an XPath request.</summary>
	/// <param name="inNode">Source node.</param>
	/// <param name="inXPath">XPath criteria.</param>
	/// <param name="outNode">Found node.</param>
	AVL_FUNCTION void Xml_SelectSingleNode
	(
		const avl::XmlNode&				 inNode,			
		const atl::String&				 inXPath,		
		atl::Conditional<avl::XmlNode>&	 outNode		
	)
	THROW_AVL_ERRORS;

	/// <summary>Selects nodes from the XML tree using XPath request.</summary>
	/// <param name="inNode">Source node.</param>
	/// <param name="inXPath">XPath criteria.</param>
	/// <param name="outNodes">Found nodes.</param>
	/// <param name="outNodeValues">Found nodes text as string.</param>
	AVL_FUNCTION void Xml_SelectMultipleNodeValues_AsStrings
	(
		const avl::XmlNode&				inNode,			
		const atl::String&				inXPath,		
		atl::Array<avl::XmlNode>&		outNodes,		
		atl::Array<atl::String>&		outNodeValues	
	)
	THROW_AVL_ERRORS;

	/// <summary>Selects nodes from the XML tree using XPath request.</summary>
	/// <param name="inNode">Source node.</param>
	/// <param name="inXPath">XPath criteria.</param>
	/// <param name="outNodes">Found nodes.</param>
	/// <param name="outNodeValues">Found nodes text as integer.</param>
	AVL_FUNCTION void Xml_SelectMultipleNodeValues_AsIntegers
	(
		const avl::XmlNode&				inNode,			
		const atl::String&				inXPath,		
		atl::Array<avl::XmlNode>&		outNodes,		
		atl::Array<int>&				outNodeValues	
	)
	THROW_AVL_ERRORS;

	/// <summary>Selects nodes from the XML tree using XPath request.</summary>
	/// <param name="inNode">Source node.</param>
	/// <param name="inXPath">XPath criteria.</param>
	/// <param name="outNodes">Found nodes.</param>
	/// <param name="outNodeValues">Found nodes text as float.</param>
	AVL_FUNCTION void Xml_SelectMultipleNodeValues_AsReals
	(
		const avl::XmlNode&				inNode,			
		const atl::String&				inXPath,		
		atl::Array<avl::XmlNode>&		outNodes,		
		atl::Array<float>&			outNodeValues	
	)
	THROW_AVL_ERRORS;

	/// <summary>Selects nodes from the XML tree using XPath request.</summary>
	/// <param name="inNode">Source node.</param>
	/// <param name="inXPath">XPath criteria.</param>
	/// <param name="outNodes">Found nodes.</param>
	/// <param name="outNodeValues">Found nodes text as bool.</param>
	AVL_FUNCTION void Xml_SelectMultipleNodeValues_AsBools
	(
		const avl::XmlNode&				inNode,			
		const atl::String&				inXPath,		
		atl::Array<avl::XmlNode>&		outNodes,		
		atl::Array<bool>&			outNodeValues		
	)
	THROW_AVL_ERRORS;

	/// <summary>Selects node from the XML tree using XPath request.</summary>
	/// <param name="inNode">Source node.</param>
	/// <param name="inXPath">XPath criteria.</param>
	/// <param name="inDefault">If no node was found default value will be used. Default value: atl::NIL.</param>
	/// <param name="outNode">Found node.</param>
	/// <param name="outNodeValue">Found node text as string.</param>
	AVL_FUNCTION void Xml_SelectSingleNodeValue_AsString
	(
		const avl::XmlNode&					inNode,			
		const atl::String&					inXPath,		
		const atl::Optional<atl::String>&	inDefault,		
		atl::Conditional<avl::XmlNode>&		outNode,		
		atl::String&						outNodeValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Selects node from the XML tree using XPath request.</summary>
	/// <param name="inNode">Source node.</param>
	/// <param name="inXPath">XPath criteria.</param>
	/// <param name="inDefault">If no node was found default value will be used. Default value: atl::NIL.</param>
	/// <param name="outNode">Found node.</param>
	/// <param name="outNodeValue">Found node text as integer.</param>
	AVL_FUNCTION void Xml_SelectSingleNodeValue_AsInteger
	(
		const avl::XmlNode&				inNode,			
		const atl::String&				inXPath,		
		const atl::Optional<int>&		inDefault,		
		atl::Conditional<avl::XmlNode>&	outNode,		
		int&							outNodeValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Selects node from the XML tree using XPath request.</summary>
	/// <param name="inNode">Source node.</param>
	/// <param name="inXPath">XPath criteria.</param>
	/// <param name="inDefault">If no node was found default value will be used. Default value: atl::NIL.</param>
	/// <param name="outNode">Found node.</param>
	/// <param name="outNodeValue">Found node text as float.</param>
	AVL_FUNCTION void Xml_SelectSingleNodeValue_AsReal
	(
		const avl::XmlNode&				inNode,			
		const atl::String&				inXPath,		
		const atl::Optional<float>& inDefault,		
		atl::Conditional<avl::XmlNode>&	outNode,		
		float&						outNodeValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Selects node from the XML tree using XPath request.</summary>
	/// <param name="inNode">Source node.</param>
	/// <param name="inXPath">XPath criteria.</param>
	/// <param name="inDefault">If no node was found default value will be used. Default value: atl::NIL.</param>
	/// <param name="outNode">Found node.</param>
	/// <param name="outNodeValue">Found node text as bool.</param>
	AVL_FUNCTION void Xml_SelectSingleNodeValue_AsBool
	(
		const avl::XmlNode&					inNode,			
		const atl::String&					inXPath,		
		const atl::Optional<bool>&			inDefault,		
		atl::Conditional<avl::XmlNode>&		outNode,		
		bool&								outNodeValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Selects attributes from the XML tree using XPath request.</summary>
	/// <param name="inNode">Source node.</param>
	/// <param name="inXPath">XPath criteria.</param>
	/// <param name="outAttributesNames">Found attributes names.</param>
	/// <param name="outAttributesValues">Found attributes values as string.</param>
	AVL_FUNCTION void Xml_SelectMultipleAttributes_AsStrings
	(
		const avl::XmlNode&				inNode,				
		const atl::String&				inXPath,			
		atl::Array<atl::String>&		outAttributesNames,	
		atl::Array<atl::String>&		outAttributesValues	
	)
	THROW_AVL_ERRORS;

	/// <summary>Selects attributes from the XML tree using XPath request.</summary>
	/// <param name="inNode">Source node.</param>
	/// <param name="inXPath">XPath criteria.</param>
	/// <param name="outAttributesNames">Found attributes names.</param>
	/// <param name="outAttributesValues">Found attributes values as integer.</param>
	AVL_FUNCTION void Xml_SelectMultipleAttributes_AsIntegers
	(
		const avl::XmlNode&				inNode,				
		const atl::String&				inXPath,			
		atl::Array<atl::String>&		outAttributesNames,	
		atl::Array<int>&				outAttributesValues	
	)
	THROW_AVL_ERRORS;

	/// <summary>Selects attributes from the XML tree using XPath request.</summary>
	/// <param name="inNode">Source node.</param>
	/// <param name="inXPath">XPath criteria.</param>
	/// <param name="outAttributesNames">Found attributes names.</param>
	/// <param name="outAttributesValues">Found attributes values as float.</param>
	AVL_FUNCTION void Xml_SelectMultipleAttributes_AsReals
	(
		const avl::XmlNode&				inNode,				
		const atl::String&				inXPath,			
		atl::Array<atl::String>&		outAttributesNames,	
		atl::Array<float>&			outAttributesValues	
	)
	THROW_AVL_ERRORS;

	/// <summary>Selects attributes from the XML tree using XPath request.</summary>
	/// <param name="inNode">Source node.</param>
	/// <param name="inXPath">XPath criteria.</param>
	/// <param name="outAttributesNames">Found attributes names.</param>
	/// <param name="outAttributesValues">Found attributes values as bool.</param>
	AVL_FUNCTION void Xml_SelectMultipleAttributes_AsBools
	(
		const avl::XmlNode&				inNode,				
		const atl::String&				inXPath,			
		atl::Array<atl::String>&		outAttributesNames,	
		atl::Array<bool>&				outAttributesValues	
	)
	THROW_AVL_ERRORS;

	/// <summary>Select attribute from the XML tree using XPath request.</summary>
	/// <param name="inNode">Source node.</param>
	/// <param name="inXPath">XPath criteria.</param>
	/// <param name="inDefault">If set this value will be returned when no attribute is found or attribute is incorrect. Default value: atl::NIL.</param>
	/// <param name="outAttributeName">Found attribute name.</param>
	/// <param name="outAttributeValue">Found attribute value as string.</param>
	AVL_FUNCTION void Xml_SelectSingleAttribute_AsString
	(
		const avl::XmlNode&					inNode,				
		const atl::String&					inXPath,			
		const atl::Optional<atl::String>&	inDefault,			
		atl::String&						outAttributeName,	
		atl::String&						outAttributeValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Select attribute from the XML tree using XPath request.</summary>
	/// <param name="inNode">Source node.</param>
	/// <param name="inXPath">XPath criteria.</param>
	/// <param name="inDefault">If set this value will be returned when no attribute is found or attribute is incorrect. Default value: atl::NIL.</param>
	/// <param name="outAttributeName">Found attribute name.</param>
	/// <param name="outAttributeValue">Found attribute value as integer.</param>
	AVL_FUNCTION void Xml_SelectSingleAttribute_AsInteger
	(
		const avl::XmlNode&			inNode,				
		const atl::String&			inXPath,			
		const atl::Optional<int>&	inDefault,			
		atl::String&				outAttributeName,	
		int&						outAttributeValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Select attribute from the XML tree using XPath request.</summary>
	/// <param name="inNode">Source node.</param>
	/// <param name="inXPath">XPath criteria.</param>
	/// <param name="inDefault">If set this value will be returned when no attribute is found or attribute is incorrect. Default value: atl::NIL.</param>
	/// <param name="outAttributeName">Found attribute name.</param>
	/// <param name="outAttributeValue">Found attribute value as float.</param>
	AVL_FUNCTION void Xml_SelectSingleAttribute_AsReal
	(
		const avl::XmlNode&				inNode,				
		const atl::String&				inXPath,			
		const atl::Optional<float>&	inDefault,			
		atl::String&					outAttributeName,	
		float&						outAttributeValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Select attribute from the XML tree using XPath request.</summary>
	/// <param name="inNode">Source node.</param>
	/// <param name="inXPath">XPath criteria.</param>
	/// <param name="inDefault">If set this value will be returned when no attribute is found or attribute is incorrect. Default value: atl::NIL.</param>
	/// <param name="outAttributeName">Found attribute name.</param>
	/// <param name="outAttributeValue">Found attribute value as bool.</param>
	AVL_FUNCTION void Xml_SelectSingleAttribute_AsBool
	(
		const avl::XmlNode&			inNode,				
		const atl::String&			inXPath,			
		const atl::Optional<bool&>	inDefault,			
		atl::String&				outAttributeName,	
		bool&						outAttributeValue	
	)
	THROW_AVL_ERRORS;

	/// <summary>Set values of attributes which were selected using XPath request.</summary>
	/// <param name="inNode">Source node.</param>
	/// <param name="inXPath">XPath criteria.</param>
	/// <param name="inValue">Value to set to attributes.</param>
	AVL_FUNCTION void Xml_SetAttributes
	(
		const avl::XmlNode&				inNode,				
		const atl::String&				inXPath,			
		const atl::String&				inValue,			
		avl::XmlNode&					outNode
	)
	THROW_AVL_ERRORS;

	/// <summary>Set values of nodes which were selected using XPath request.</summary>
	/// <param name="inNode">Source node.</param>
	/// <param name="inXPath">XPath criteria.</param>
	/// <param name="inText">Value to set to nodes.</param>
	AVL_FUNCTION void Xml_SetNodeValues
	(
		const avl::XmlNode&				inNode,				
		const atl::String&				inXPath,			
		const atl::String&				inText,			
		avl::XmlNode&					outNode
	)
	THROW_AVL_ERRORS;

} // namespace avl

#endif // AVL_XML_H

