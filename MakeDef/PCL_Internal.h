#ifndef __PCL_INTERNAL_H__
#define __PCL_INTERNAL_H__

#ifndef __PCL_H__
#	error Do not include this file directly. Include "PCL.h" instead
#endif

#define PCL_VIRTUAL_CLASSCODE(ClassName,IsContainer) \
static const uint V##ClassName##ClassCode = VIRTUALCODE(IsContainer);

#define PCL_GENERIC_CLASSCODE(ClassName,BaseClassCode) \
static const uint ClassName##ClassCode = CLASSCODE(BaseClassCode);

#define PCL_CLASSCODE(ClassName,BaseClassCode) \
static const uint L##ClassName##ClassCode = CLASSCODE(BaseClassCode);

#define PCL_GENERIC_CLASSCODE_IMPL(ClassName) \
public: static const uint ClassCode() {return ClassName##ClassCode;};

#define PCL_CLASSCODE_IMPL(ClassName) \
public: static const uint ClassCode() {return L##ClassName##ClassCode;};

#define PCL_CONTAINER_DECL(ClassName) \
L##ClassName(const pcont pContainer); \
virtual void Import(const pcont pContainer, bool AutoRelease = true); \
virtual const pcont Export(void);

#define PCL_GENERIC_CONTAINER_DECL(ClassName) \
G##ClassName(const pcont pContainer); \
virtual void Import(const pcont pContainer, bool AutoRelease = true); \
virtual const pcont Export(void);

#define PCL_VIRTUAL_CLASS(x) PCL_VIRTUAL_CLASSCODE(x,false) \
class V##x { \
public

#define PCL_VIRTUAL_CLASS_OF(y,x) PCL_VIRTUAL_CLASSCODE(x,false) \
class V##x : public y { \
public

#define PCL_VIRTUAL_CONTAINER(x) PCL_VIRTUAL_CLASSCODE(x,true) \
class V##x : public VContainer { \
public

#define PCL_VIRTUAL_CONTAINER_OF(y,x) PCL_VIRTUAL_CLASSCODE(x,true) \
class V##x : public VContainer, public V##y { \
public

#define PCL_GENERIC_CLASS(x) PCL_GENERIC_CLASSCODE(G##x,V##x##ClassCode) \
class PCL_API G##x : public V##x { PCL_GENERIC_CLASSCODE_IMPL(G##x) \
protected: G##x(); virtual ~G##x(); \
protected

#define PCL_CLASS(x) PCL_CLASSCODE(x,V##x##ClassCode) \
class PCL_API L##x : public V##x { PCL_CLASSCODE_IMPL(x) \
public

#define PCL_CLASS_OF(y,x) PCL_CLASSCODE(x,y##ClassCode) \
class PCL_API L##x : public y { PCL_CLASSCODE_IMPL(x) \
public

#define PCL_GENERIC_CONTAINER(x) PCL_GENERIC_CLASSCODE(G##x,V##x##ClassCode) \
class PCL_API G##x : public V##x { PCL_GENERIC_CLASSCODE_IMPL(G##x) \
protected: G##x(); virtual ~G##x(); \
PCL_GENERIC_CONTAINER_DECL(x) \
protected

#define PCL_CONTAINER(x) PCL_CLASSCODE(x,V##x##ClassCode) \
class PCL_API L##x : public V##x { PCL_CLASSCODE_IMPL(x) \
public: PCL_CONTAINER_DECL(x) \
public

#define PCL_CONTAINER_OF(y,x) PCL_CLASSCODE(x,y##ClassCode) \
class PCL_API L##x : public y { PCL_CLASSCODE_IMPL(x) \
public: PCL_CONTAINER_DECL(x) \
public

#define PCL_ENUMERATOR(x) typedef enum PCL_##x { ZNull##x = 0,

#define PCL_FPTR(t,x) typedef t (*x)

#endif // __PCL_INTERNAL_H__
