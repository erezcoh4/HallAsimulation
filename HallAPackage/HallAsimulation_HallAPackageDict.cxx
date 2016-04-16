// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME HallAsimulation_HallAPackageDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "TAnalysisSIMC.h"
#include "TSIMC.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *TSIMC_Dictionary();
   static void TSIMC_TClassManip(TClass*);
   static void *new_TSIMC(void *p = 0);
   static void *newArray_TSIMC(Long_t size, void *p);
   static void delete_TSIMC(void *p);
   static void deleteArray_TSIMC(void *p);
   static void destruct_TSIMC(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TSIMC*)
   {
      ::TSIMC *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::TSIMC));
      static ::ROOT::TGenericClassInfo 
         instance("TSIMC", "TSIMC.h", 25,
                  typeid(::TSIMC), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &TSIMC_Dictionary, isa_proxy, 4,
                  sizeof(::TSIMC) );
      instance.SetNew(&new_TSIMC);
      instance.SetNewArray(&newArray_TSIMC);
      instance.SetDelete(&delete_TSIMC);
      instance.SetDeleteArray(&deleteArray_TSIMC);
      instance.SetDestructor(&destruct_TSIMC);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TSIMC*)
   {
      return GenerateInitInstanceLocal((::TSIMC*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TSIMC*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TSIMC_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TSIMC*)0x0)->GetClass();
      TSIMC_TClassManip(theClass);
   return theClass;
   }

   static void TSIMC_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *TAnalysisSIMC_Dictionary();
   static void TAnalysisSIMC_TClassManip(TClass*);
   static void *new_TAnalysisSIMC(void *p = 0);
   static void *newArray_TAnalysisSIMC(Long_t size, void *p);
   static void delete_TAnalysisSIMC(void *p);
   static void deleteArray_TAnalysisSIMC(void *p);
   static void destruct_TAnalysisSIMC(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TAnalysisSIMC*)
   {
      ::TAnalysisSIMC *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::TAnalysisSIMC));
      static ::ROOT::TGenericClassInfo 
         instance("TAnalysisSIMC", "TAnalysisSIMC.h", 29,
                  typeid(::TAnalysisSIMC), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &TAnalysisSIMC_Dictionary, isa_proxy, 4,
                  sizeof(::TAnalysisSIMC) );
      instance.SetNew(&new_TAnalysisSIMC);
      instance.SetNewArray(&newArray_TAnalysisSIMC);
      instance.SetDelete(&delete_TAnalysisSIMC);
      instance.SetDeleteArray(&deleteArray_TAnalysisSIMC);
      instance.SetDestructor(&destruct_TAnalysisSIMC);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TAnalysisSIMC*)
   {
      return GenerateInitInstanceLocal((::TAnalysisSIMC*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TAnalysisSIMC*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TAnalysisSIMC_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TAnalysisSIMC*)0x0)->GetClass();
      TAnalysisSIMC_TClassManip(theClass);
   return theClass;
   }

   static void TAnalysisSIMC_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_TSIMC(void *p) {
      return  p ? new(p) ::TSIMC : new ::TSIMC;
   }
   static void *newArray_TSIMC(Long_t nElements, void *p) {
      return p ? new(p) ::TSIMC[nElements] : new ::TSIMC[nElements];
   }
   // Wrapper around operator delete
   static void delete_TSIMC(void *p) {
      delete ((::TSIMC*)p);
   }
   static void deleteArray_TSIMC(void *p) {
      delete [] ((::TSIMC*)p);
   }
   static void destruct_TSIMC(void *p) {
      typedef ::TSIMC current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TSIMC

namespace ROOT {
   // Wrappers around operator new
   static void *new_TAnalysisSIMC(void *p) {
      return  p ? new(p) ::TAnalysisSIMC : new ::TAnalysisSIMC;
   }
   static void *newArray_TAnalysisSIMC(Long_t nElements, void *p) {
      return p ? new(p) ::TAnalysisSIMC[nElements] : new ::TAnalysisSIMC[nElements];
   }
   // Wrapper around operator delete
   static void delete_TAnalysisSIMC(void *p) {
      delete ((::TAnalysisSIMC*)p);
   }
   static void deleteArray_TAnalysisSIMC(void *p) {
      delete [] ((::TAnalysisSIMC*)p);
   }
   static void destruct_TAnalysisSIMC(void *p) {
      typedef ::TAnalysisSIMC current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TAnalysisSIMC

namespace ROOT {
   static TClass *vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = 0);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "vector", 477,
                  typeid(vector<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<int>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<int>*)0x0)->GetClass();
      vectorlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete ((vector<int>*)p);
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] ((vector<int>*)p);
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<int>

namespace ROOT {
   static TClass *vectorlETVector3gR_Dictionary();
   static void vectorlETVector3gR_TClassManip(TClass*);
   static void *new_vectorlETVector3gR(void *p = 0);
   static void *newArray_vectorlETVector3gR(Long_t size, void *p);
   static void delete_vectorlETVector3gR(void *p);
   static void deleteArray_vectorlETVector3gR(void *p);
   static void destruct_vectorlETVector3gR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TVector3>*)
   {
      vector<TVector3> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TVector3>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TVector3>", -2, "vector", 477,
                  typeid(vector<TVector3>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETVector3gR_Dictionary, isa_proxy, 4,
                  sizeof(vector<TVector3>) );
      instance.SetNew(&new_vectorlETVector3gR);
      instance.SetNewArray(&newArray_vectorlETVector3gR);
      instance.SetDelete(&delete_vectorlETVector3gR);
      instance.SetDeleteArray(&deleteArray_vectorlETVector3gR);
      instance.SetDestructor(&destruct_vectorlETVector3gR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TVector3> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<TVector3>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETVector3gR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TVector3>*)0x0)->GetClass();
      vectorlETVector3gR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETVector3gR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETVector3gR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TVector3> : new vector<TVector3>;
   }
   static void *newArray_vectorlETVector3gR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TVector3>[nElements] : new vector<TVector3>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETVector3gR(void *p) {
      delete ((vector<TVector3>*)p);
   }
   static void deleteArray_vectorlETVector3gR(void *p) {
      delete [] ((vector<TVector3>*)p);
   }
   static void destruct_vectorlETVector3gR(void *p) {
      typedef vector<TVector3> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TVector3>

namespace ROOT {
   static TClass *vectorlETStringgR_Dictionary();
   static void vectorlETStringgR_TClassManip(TClass*);
   static void *new_vectorlETStringgR(void *p = 0);
   static void *newArray_vectorlETStringgR(Long_t size, void *p);
   static void delete_vectorlETStringgR(void *p);
   static void deleteArray_vectorlETStringgR(void *p);
   static void destruct_vectorlETStringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TString>*)
   {
      vector<TString> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TString>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TString>", -2, "vector", 477,
                  typeid(vector<TString>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETStringgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TString>) );
      instance.SetNew(&new_vectorlETStringgR);
      instance.SetNewArray(&newArray_vectorlETStringgR);
      instance.SetDelete(&delete_vectorlETStringgR);
      instance.SetDeleteArray(&deleteArray_vectorlETStringgR);
      instance.SetDestructor(&destruct_vectorlETStringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TString> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<TString>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETStringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TString>*)0x0)->GetClass();
      vectorlETStringgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETStringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETStringgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TString> : new vector<TString>;
   }
   static void *newArray_vectorlETStringgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TString>[nElements] : new vector<TString>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETStringgR(void *p) {
      delete ((vector<TString>*)p);
   }
   static void deleteArray_vectorlETStringgR(void *p) {
      delete [] ((vector<TString>*)p);
   }
   static void destruct_vectorlETStringgR(void *p) {
      typedef vector<TString> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TString>

namespace ROOT {
   static TClass *vectorlETLorentzVectorgR_Dictionary();
   static void vectorlETLorentzVectorgR_TClassManip(TClass*);
   static void *new_vectorlETLorentzVectorgR(void *p = 0);
   static void *newArray_vectorlETLorentzVectorgR(Long_t size, void *p);
   static void delete_vectorlETLorentzVectorgR(void *p);
   static void deleteArray_vectorlETLorentzVectorgR(void *p);
   static void destruct_vectorlETLorentzVectorgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TLorentzVector>*)
   {
      vector<TLorentzVector> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TLorentzVector>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TLorentzVector>", -2, "vector", 477,
                  typeid(vector<TLorentzVector>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETLorentzVectorgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<TLorentzVector>) );
      instance.SetNew(&new_vectorlETLorentzVectorgR);
      instance.SetNewArray(&newArray_vectorlETLorentzVectorgR);
      instance.SetDelete(&delete_vectorlETLorentzVectorgR);
      instance.SetDeleteArray(&deleteArray_vectorlETLorentzVectorgR);
      instance.SetDestructor(&destruct_vectorlETLorentzVectorgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TLorentzVector> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<TLorentzVector>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETLorentzVectorgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TLorentzVector>*)0x0)->GetClass();
      vectorlETLorentzVectorgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETLorentzVectorgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETLorentzVectorgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TLorentzVector> : new vector<TLorentzVector>;
   }
   static void *newArray_vectorlETLorentzVectorgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TLorentzVector>[nElements] : new vector<TLorentzVector>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETLorentzVectorgR(void *p) {
      delete ((vector<TLorentzVector>*)p);
   }
   static void deleteArray_vectorlETLorentzVectorgR(void *p) {
      delete [] ((vector<TLorentzVector>*)p);
   }
   static void destruct_vectorlETLorentzVectorgR(void *p) {
      typedef vector<TLorentzVector> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TLorentzVector>

namespace {
  void TriggerDictionaryInitialization_libHallAsimulation_HallAPackage_Impl() {
    static const char* headers[] = {
"TAnalysisSIMC.h",
"TSIMC.h",
0
    };
    static const char* includePaths[] = {
"/Users/erezcohen/larlite/UserDev/mySoftware",
"/usr/local/Cellar/root6/6.06.02/include/root",
"/Users/erezcohen/larlite/UserDev/HallAsimulation/HallAPackage/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libHallAsimulation_HallAPackage dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$TAnalysisSIMC.h")))  TVector3;
namespace std{inline namespace __1{template <class _Tp> class __attribute__((annotate("$clingAutoload$string")))  allocator;
}}
class __attribute__((annotate("$clingAutoload$TAnalysisSIMC.h")))  TLorentzVector;
class __attribute__((annotate("$clingAutoload$TSIMC.h")))  TSIMC;
class __attribute__((annotate("$clingAutoload$TAnalysisSIMC.h")))  TAnalysisSIMC;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libHallAsimulation_HallAPackage dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "TAnalysisSIMC.h"
#include "TSIMC.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"TAnalysisSIMC", payloadCode, "@",
"TSIMC", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libHallAsimulation_HallAPackage",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libHallAsimulation_HallAPackage_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libHallAsimulation_HallAPackage_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libHallAsimulation_HallAPackage() {
  TriggerDictionaryInitialization_libHallAsimulation_HallAPackage_Impl();
}
