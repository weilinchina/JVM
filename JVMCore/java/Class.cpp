/**=============================================================================
 ** Copyright (C) 2011- WEILin beijing.
 ** =============================================================================
 **
 ** This document contains proprietary information belonging to gemalto.
 ** Technologies. Passing on and copying of this document, use and communication
 ** of its contents is not permitted without prior written authorisation.
 **
 ** =============================================================================
 **	Information :
 ** Project          : JVMCore $
 **	File Name        : Class.cpp $
 **	Created on       : Nov 13, 2012 $
 **	Time             : 5:51:21 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "Class.h"

#include "JVMUtility.h"
#include "AccessFlags.h"
#include "ConstantClass.h"
#include "ConstantUtf8.h"
#include "Package.h"


namespace diamon_jvm
{

Class::Class()
{
	this->magic_ = 0;
	this->minor_version_ = 0;
	this->major_version_ = 0;
	this->constant_count_ = 0;
	this->constants_ = NULL;
	this->access_flags_ = 0;
	this->this_class_ = 0;
	this->super_class_ = 0;
	this->interfaces_count_ = 0;
	this->interfaces_ = NULL;
	this->fields_count_ = 0;
	this->fields_ = NULL;
	this->methods_count_ = 0;
	this->methods_ = NULL;

	this->version_ = 0;
	this->name_ = "";
	this->pureName_ = "";
	this->superClassName_ = "";
	this->interfaceNames_.clear();
	this->attributeInnerClasses_ = NULL;
	this->attributeEnclosingMethod_ = NULL;
	this->attributeSignature_ = NULL;
	this->attributeSourceFile_ = NULL;
	this->attributeSourceDebugExtension_ = NULL;
	this->deprecated_ = false;
	this->attributeBootstrapMethods_ = NULL;

	this->package_ = NULL;
	this->classLoader_ = NULL;
}

Class::~Class()
{
	if(this->constants_ != NULL)
	{
		for(int i = 0; i < this->constant_count_ - 1; i++)
		{
			Constant *constant = this->constants_[i];
			if(constant != NULL)
				delete constant;
		}
		delete[] this->constants_;
		this->constants_ = NULL;
	}

	if(this->interfaces_ != NULL)
	{
		delete[] this->interfaces_;
		this->interfaces_ = NULL;
	}

	if(this->fields_ != NULL)
	{
		for(int i = 0; i < this->fields_count_; i++)
		{
			Field *javaField = this->fields_[i];
			delete javaField;
		}
		delete[] this->fields_;
		this->fields_ = NULL;
	}

	if(this->methods_ != NULL)
	{
		for(int i = 0; i < this->methods_count_; i++)
		{
			Method *javaMethod = this->methods_[i];
			delete javaMethod;
		}
		delete[] this->methods_;
		this->methods_ = NULL;
	}

	if(this->attributeInnerClasses_ != NULL)
	{
		delete this->attributeInnerClasses_;
		this->attributeInnerClasses_ = NULL;
	}

	if(this->attributeEnclosingMethod_ != NULL)
	{
		delete this->attributeEnclosingMethod_;
		this->attributeEnclosingMethod_ = NULL;
	}

	if(this->attributeSignature_ != NULL)
	{
		delete this->attributeSignature_;
		this->attributeSignature_ = NULL;
	}

	if(this->attributeSourceFile_ != NULL)
	{
		delete this->attributeSourceFile_;
		this->attributeSourceFile_ = NULL;
	}

	if(this->attributeSourceDebugExtension_ != NULL)
	{
		delete this->attributeSourceDebugExtension_;
		this->attributeSourceDebugExtension_ = NULL;
	}

	if(this->attributeBootstrapMethods_ != NULL)
	{
		delete this->attributeBootstrapMethods_;
		this->attributeBootstrapMethods_ = NULL;
	}
}

JVM_U2 Class::getAccessFlags() const
{
	return access_flags_;
}

const Constant *Class::getConstant(JVM_U2 at) const
{
	return Constant::getConstant(at, this->constant_count_, this->constants_);
}

JVM_U2 Class::getConstantCount() const
{
	return (JVM_U2)(this->constant_count_);
}

const Field *Class::getField(JVM_U2 at) const
{
	return Field::getField(at, this->fields_count_, this->fields_);
}

JVM_U2 Class::getFieldsCount() const
{
	return this->fields_count_;
}

JVM_U2 Class::getInterface(JVM_U2 at) const
{
	ASSERT(at >= 0 && at <= interfaces_count_ - 1);

	return this->interfaces_[at];
}

JVM_U2 Class::getInterfacesCount() const
{
	return this->interfaces_count_;
}

JVM_U4 Class::getMagic() const
{
	return magic_;
}

JVM_U2 Class::getMajorVersion() const
{
	return major_version_;
}

const Method *Class::getMethod(JVM_U2 at) const
{
	return Method::getMethod(at, this->methods_count_, this->methods_);
}

JVM_U2 Class::getMethodsCount() const
{
	return this->methods_count_;
}

JVM_U2 Class::getMinorVersion() const
{
	return minor_version_;
}

JVM_U2 Class::getSuperClass() const
{
	return super_class_;
}

JVM_U2 Class::getThisClass() const
{
	return this_class_;
}

JVM_DOUBLE Class::getVersion() const
{
	return version_;
}

const std::string &Class::getName() const
{
	return name_;
}

const std::string &Class::getPureName() const
{
	return pureName_;
}

const std::string &Class::getSuperClassName() const
{
	return superClassName_;
}

const std::vector<std::string> &Class::getInterfaceNames() const
{
	return interfaceNames_;
}

const AttributeInnerClasses *Class::getAttributeInnerClasses() const
{
	return attributeInnerClasses_;
}

const AttributeEnclosingMethod *Class::getAttributeEnclosingMethod() const
{
	return attributeEnclosingMethod_;
}

const AttributeSignature *Class::getAttributeSignature() const
{
	return attributeSignature_;
}

const AttributeSourceFile *Class::getAttributeSourceFile() const
{
	return attributeSourceFile_;
}

const AttributeSourceDebugExtension *Class::getAttributeSourceDebugExtension() const
{
	return attributeSourceDebugExtension_;
}

bool Class::isDeprecated()
{
	return deprecated_;
}

const AttributeBootstrapMethods *Class::getAttributeBootstrapMethods() const
{
	return attributeBootstrapMethods_;
}

const Package &Class::getPackage() const
{
	ASSERT(this->package_ != NULL);

	return *package_;
}

const ClassLoader &Class::getClassLoader() const
{
	ASSERT(this->classLoader_ != NULL);

	return *classLoader_;
}

bool Class::marshal(Stream & stream)
{
	// read @magic
	size_t size = stream.readBytes((JVM_BYTE*)(&this->magic_), sizeof(this->magic_));
	if(size != sizeof(this->magic_))
	{
		ERROR("read magic of Class failed!");
		return false;
	}
	this->magic_ = swap_JVM_U4(this->magic_);
	if(this->magic_ != 0xCAFEBABE)
	{
		ERROR("check magic of Class failed! it should be \"0xCAFEBABE\".");
		return false;
	}

	// read @minor_version & @major_version
	size = stream.readBytes((JVM_BYTE*)(&this->minor_version_), sizeof(this->minor_version_));
	if(size != sizeof(this->minor_version_))
	{
		ERROR("read minor_version of Class failed!");
		return false;
	}
	this->minor_version_ = swap_JVM_U2(this->minor_version_);
	size = stream.readBytes((JVM_BYTE*)(&this->major_version_), sizeof(this->major_version_));
	if(size != sizeof(this->major_version_))
	{
		ERROR("read major_version of Class failed!");
		return false;
	}
	this->major_version_ = swap_JVM_U2(this->major_version_);
	this->version_ = combine_JVM_DOUBLE(this->major_version_, this->minor_version_);
	if(this->version_ < 45.0 || this->version_ > 51.65535)
	{
		ERROR("check major_version & minor_version of Class failed!");
		return false;
	}

	// read @constant_count
	size = stream.readBytes((JVM_BYTE*)(&this->constant_count_), sizeof(this->constant_count_));
	if(size != sizeof(this->constant_count_))
	{
		ERROR("read constant_count of Class failed!");
		return false;
	}
	this->constant_count_ = swap_JVM_U2(this->constant_count_);

	// read @constant_pool
	if(this->constant_count_ > 1)
	{
		this->constants_ = new Constant *[this->constant_count_ - 1];
		if(this->constants_ == NULL)
		{
			ERROR("allocate memory for constants of Class failed!");
			return false;
		}
		for(int i = 0; i < this->constant_count_ - 1; i ++)
		{
			JVM_U1 tag = 0;
			size = stream.readBytes((JVM_BYTE *)&tag, sizeof(tag));
			if(size != sizeof(tag))
			{
				ERROR("read tag of constant %d of Class failed!", i);
				return false;
			}
			Constant *constant = Constant::dispatchMarshal(stream, tag);
			if(constant == NULL)
			{
				ERROR("dispatch marshal of constant %d of Class failed!", i);
				return false;
			}
			this->constants_[i] = constant;
			if(constant->getTag() == 5 || constant->getTag() == 6)
			{
				i += 1;
				if(i < this->constant_count_ - 1)
					this->constants_[i] = NULL;
			}
		}
	}

	// read @access_flags
	size = stream.readBytes((JVM_BYTE*)(&this->access_flags_), sizeof(this->access_flags_));
	if(size != sizeof(this->access_flags_))
	{
		ERROR("read access_flags of Class failed!");
		return false;
	}
	this->access_flags_ = swap_JVM_U2(this->access_flags_);
	/*
	 if(this->access_flags_ & (~CLASS_ACC_FLAGS))
	 {
	 ERROR("check access_flags of Class failed!");
	 return false;
	 }
	 */

	// read @this_class
	size = stream.readBytes((JVM_BYTE*)(&this->this_class_), sizeof(this->this_class_));
	if(size != sizeof(this->this_class_))
	{
		ERROR("read this_class of Class failed!");
		return false;
	}
	this->this_class_ = swap_JVM_U2(this->this_class_);
	if(this->this_class_ < 1 || this->this_class_ > this->constant_count_)
	{
		ERROR("check scope of this_class of Class failed!");
		return false;
	}
	ConstantClass *javaCPClass_className = (ConstantClass *)(this->getConstant(this->this_class_));
	if(javaCPClass_className != NULL)
	{
		ConstantUtf8 *javaCPUtf8_className = (ConstantUtf8 *)(this->getConstant(javaCPClass_className->getNameIndex()));
		if(javaCPUtf8_className != NULL)
		{
			this->name_.assign((char*)(javaCPUtf8_className->getBytes()), javaCPUtf8_className->getLength());
			TRACE("class name is: %s", this->name_.c_str());
			size_t pos = this->name_.find_last_of(PACKAGE_SEPARATOR);
			if(pos != std::string::npos)
				this->pureName_ = this->name_.substr(pos + 1);
			else
				this->pureName_ = this->name_;
			TRACE("class pure name is: %s", this->pureName_.c_str());
		}
	}

	// read @super_class
	size = stream.readBytes((JVM_BYTE*)(&this->super_class_), sizeof(this->super_class_));
	if(size != sizeof(this->super_class_))
	{
		ERROR("read super_class of Class failed!");
		return false;
	}
	this->super_class_ = swap_JVM_U2(this->super_class_);
	if(this->super_class_ != 0)
	{
		if(this->super_class_ < 1 || this->super_class_ > this->constant_count_)
		{
			ERROR("check scope of super_class of Class failed!");
			return false;
		}
		ConstantClass *javaCPClass_superClassName = (ConstantClass *)(this->getConstant(this->super_class_));
		if(javaCPClass_superClassName != NULL)
		{
			ConstantUtf8 *javaCPUtf8_superClassName = (ConstantUtf8 *)(this->getConstant(javaCPClass_superClassName->getNameIndex()));
			if(javaCPUtf8_superClassName != NULL)
			{
				this->superClassName_.assign((char*)(javaCPUtf8_superClassName->getBytes()), javaCPUtf8_superClassName->getLength());
				TRACE("super class name is: %s", this->superClassName_.c_str());
			}
		}
	}

	// read @interfaces_count
	size = stream.readBytes((JVM_BYTE*)(&this->interfaces_count_), sizeof(this->interfaces_count_));
	if(size != sizeof(this->interfaces_count_))
	{
		ERROR("read interfaces_count of Class failed!");
		return false;
	}
	this->interfaces_count_ = swap_JVM_U2(this->interfaces_count_);

	// read @interfaces
	if(this->interfaces_count_ > 0)
	{
		this->interfaces_ = new JVM_U2[this->interfaces_count_];
		if(this->interfaces_ == NULL)
		{
			ERROR("allocate memory for interfaces of Class failed!");
			return false;
		}
		for(int i = 0; i < this->interfaces_count_; i++)
		{
			size = stream.readBytes((JVM_BYTE*)(&this->interfaces_[i]), sizeof(this->interfaces_[i]));
			if(size != sizeof(this->interfaces_[i]))
			{
				ERROR("read interface %d of Class failed!", i);
				return false;
			}
			this->interfaces_[i] = swap_JVM_U2(this->interfaces_[i]);
			ConstantClass *javaCPClass_interface = (ConstantClass *)(this->getConstant(this->interfaces_[i]));
			if(javaCPClass_interface != NULL)
			{
				ConstantUtf8 *javaCPUtf8_interface = (ConstantUtf8 *)(this->getConstant(javaCPClass_interface->getNameIndex()));
				if(javaCPUtf8_interface != NULL)
				{
					std::string interfaceName((char*)(javaCPUtf8_interface->getBytes()), javaCPUtf8_interface->getLength());
					this->interfaceNames_.push_back(interfaceName);
					TRACE("interface name is: %s", interfaceName.c_str());
				}
			}
		}

	}

	// read @fields_count
	size = stream.readBytes((JVM_BYTE*)(&this->fields_count_), sizeof(this->fields_count_));
	if(size != sizeof(this->fields_count_))
	{
		ERROR("read fields_count of Class failed!");
		return false;
	}
	this->fields_count_ = swap_JVM_U2(this->fields_count_);

	// @fields
	if(this->fields_count_ > 0)
	{
		this->fields_ = new Field*[this->fields_count_];
		if(this->fields_ == NULL)
		{
			ERROR("allocate memory for fields of Class failed!");
			return false;
		}
		for(int i = 0; i < this->fields_count_; i++)
		{
			Field *javaField = new Field();
			if(javaField == NULL)
			{
				ERROR("allocate memory for field %d of Class failed!", i);
				return false;
			}
			javaField->constant_count_ = this->constant_count_;
			javaField->constants_ = this->constants_;
			if(javaField->marshal(stream) == false)
			{
				ERROR("marshal field %d of Class failed!", i);
				return false;
			}
			this->fields_[i] = javaField;
		}

	}

	// read @methods_count
	size = stream.readBytes((JVM_BYTE*)(&this->methods_count_), sizeof(this->methods_count_));
	if(size != sizeof(this->methods_count_))
	{
		ERROR("read methods_count of Class failed!");
		return false;
	}
	this->methods_count_ = swap_JVM_U2(this->methods_count_);

	// read @methods
	if(this->methods_count_ > 0)
	{
		this->methods_ = new Method*[this->methods_count_];
		if(this->methods_ == NULL)
		{
			ERROR("allocate memory for methods of Class failed!");
			return false;
		}
		for(int i = 0; i < this->methods_count_; i++)
		{
			Method *javaMethod = new Method();
			if(javaMethod == NULL)
			{
				ERROR("allocate memory for method %d of Class failed!", i);
				return false;
			}
			javaMethod->constant_count_ = this->constant_count_;
			javaMethod->constants_ = this->constants_;
			if(javaMethod->marshal(stream) == false)
			{
				ERROR("marshal method %d of Class failed!", i);
				return false;
			}
			this->methods_[i] = javaMethod;
		}

	}

	// read @attributes_count_
	JVM_U2 attributes_count = 0;
	size = stream.readBytes((JVM_BYTE*)(&attributes_count), sizeof(attributes_count));
	if(size != sizeof(attributes_count))
	{
		ERROR("read attributes_count of Class failed!");
		return false;
	}
	attributes_count = swap_JVM_U2(attributes_count);

	// read @attributes_
	if(attributes_count > 0)
	{
		for(size_t i = 0; i < attributes_count; i++)
		{
			// read @attribute_name_index
			JVM_U2 attribute_name_index = 0;
			size_t size = stream.readBytes((JVM_BYTE *)(&attribute_name_index), sizeof(attribute_name_index));
			if(size != sizeof(attribute_name_index))
			{
				ERROR("read attribute_name_index %d of Class failed!", i);
				return false;
			}
			attribute_name_index = swap_JVM_U2(attribute_name_index);
			ConstantUtf8 *javaCPUtf8_name = (ConstantUtf8 *)Constant::getConstant(attribute_name_index, this->constant_count_, this->constants_);
			if(javaCPUtf8_name == NULL)
			{
				ERROR("locate attribute_name by attribute_name_index #%d of Class failed!", attribute_name_index);
				return false;
			}
			std::string attributeName((char *)(javaCPUtf8_name->getBytes()), javaCPUtf8_name->getLength());
			TRACE("attribute name is: %s", attributeName.c_str());

			// read @attribute_length
			JVM_U4 attribute_length = 0;
			size = stream.readBytes((JVM_BYTE*)(&attribute_length), sizeof(attribute_length));
			if(size != sizeof(attribute_length))
			{
				ERROR("read attribute_length %d of Class failed!", i);
				return false;
			}
			attribute_length = swap_JVM_U4(attribute_length);

			if(attributeName.compare("InnerClasses") == 0)
			{
				this->attributeInnerClasses_ = new AttributeInnerClasses();
				if(this->attributeInnerClasses_ == NULL)
				{
					ERROR("allocate memory for AttributeInnerClasses of Class failed!");
					return false;
				}
				this->attributeInnerClasses_->attribute_name_index_ = attribute_name_index;
				this->attributeInnerClasses_->attribute_length_ = attribute_length;
				this->attributeInnerClasses_->attributeName_ = attributeName;
				this->attributeInnerClasses_->constant_count_ = this->constant_count_;
				this->attributeInnerClasses_->constants_ = this->constants_;
				if(this->attributeInnerClasses_->marshal(stream) == false)
				{
					ERROR("marshal AttributeInnerClasses of Class failed!");
					return false;
				}
			}
			else if(attributeName.compare("EnclosingMethod") == 0)
			{
				this->attributeEnclosingMethod_ = new AttributeEnclosingMethod();
				if(this->attributeEnclosingMethod_ == NULL)
				{
					ERROR("allocate memory for AttributeEnclosingMethod of Class failed!");
					return false;
				}
				this->attributeEnclosingMethod_->attribute_name_index_ = attribute_name_index;
				this->attributeEnclosingMethod_->attribute_length_ = attribute_length;
				this->attributeEnclosingMethod_->attributeName_ = attributeName;
				this->attributeEnclosingMethod_->constant_count_ = this->constant_count_;
				this->attributeEnclosingMethod_->constants_ = this->constants_;
				if(this->attributeEnclosingMethod_->marshal(stream) == false)
				{
					ERROR("marshal AttributeEnclosingMethod of Class failed!");
					return false;
				}
			}
			else if(attributeName.compare("Synthetic") == 0)
			{
				TRACE("set flag ACC_SYNTHETIC for class.");
				this->access_flags_ |= ACC_SYNTHETIC;
			}
			// for class file version equals or above 49.0
			else if(attributeName.compare("Signature") == 0)
			{
				this->attributeSignature_ = new AttributeSignature();
				if(this->attributeSignature_ == NULL)
				{
					ERROR("allocate memory for AttributeSignature of Class failed!");
					return false;
				}
				this->attributeSignature_->attribute_name_index_ = attribute_name_index;
				this->attributeSignature_->attribute_length_ = attribute_length;
				this->attributeSignature_->attributeName_ = attributeName;
				this->attributeSignature_->constant_count_ = this->constant_count_;
				this->attributeSignature_->constants_ = this->constants_;
				if(this->attributeSignature_->marshal(stream) == false)
				{
					ERROR("marshal AttributeSignature of Class failed!");
					return false;
				}
			}
			else if(attributeName.compare("SourceFile") == 0)
			{
				this->attributeSourceFile_ = new AttributeSourceFile();
				if(this->attributeSourceFile_ == NULL)
				{
					ERROR("allocate memory for AttributeSourceFile of Class failed!");
					return false;
				}
				this->attributeSourceFile_->attribute_name_index_ = attribute_name_index;
				this->attributeSourceFile_->attribute_length_ = attribute_length;
				this->attributeSourceFile_->attributeName_ = attributeName;
				this->attributeSourceFile_->constant_count_ = this->constant_count_;
				this->attributeSourceFile_->constants_ = this->constants_;
				if(this->attributeSourceFile_->marshal(stream) == false)
				{
					ERROR("marshal AttributeSourceFile of Class failed!");
					return false;
				}
			}
			else if(attributeName.compare("SourceDebugExtension") == 0)
			{
				this->attributeSourceDebugExtension_ = new AttributeSourceDebugExtension();
				if(this->attributeSourceDebugExtension_ == NULL)
				{
					ERROR("allocate memory for AttributeSourceDebugExtension of Class failed!");
					return false;
				}
				this->attributeSourceDebugExtension_->attribute_name_index_ = attribute_name_index;
				this->attributeSourceDebugExtension_->attribute_length_ = attribute_length;
				this->attributeSourceDebugExtension_->attributeName_ = attributeName;
				this->attributeSourceDebugExtension_->constant_count_ = this->constant_count_;
				this->attributeSourceDebugExtension_->constants_ = this->constants_;
				if(this->attributeSourceDebugExtension_->marshal(stream) == false)
				{
					ERROR("marshal AttributeSourceDebugExtension of Class failed!");
					return false;
				}
			}
			else if(attributeName.compare("Deprecated") == 0)
			{
				TRACE("set flag DEPRECATED for class.");
				this->deprecated_ = true;
			}
			else if(attributeName.compare("BootstrapMethods") == 0)
			{
				this->attributeBootstrapMethods_ = new AttributeBootstrapMethods();
				if(this->attributeBootstrapMethods_ == NULL)
				{
					ERROR("allocate memory for AttributeBootstrapMethods of Class failed!");
					return false;
				}
				this->attributeBootstrapMethods_->attribute_name_index_ = attribute_name_index;
				this->attributeBootstrapMethods_->attribute_length_ = attribute_length;
				this->attributeBootstrapMethods_->attributeName_ = attributeName;
				this->attributeBootstrapMethods_->constant_count_ = this->constant_count_;
				this->attributeBootstrapMethods_->constants_ = this->constants_;
				if(this->attributeBootstrapMethods_->marshal(stream) == false)
				{
					ERROR("marshal AttributeBootstrapMethods of Class failed!");
					return false;
				}
			}
			else
			{
				if(Attribute::marshal(stream, attribute_name_index, attribute_length) == false)
				{
					ERROR("marshal attribute %d of Class failed!", i);
					return false;
				}
			}
		}
	}

	return true;
}

} /* namespace diamon_jvm */
