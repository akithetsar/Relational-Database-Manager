
#include "database_DatabaseWrapper.h"
#include "Database.h"
#include <memory>



std::shared_ptr<Database> db;
std::string jstringToString(JNIEnv *env, jstring jStr) {
    if (!jStr) return "";
    const jclass stringClass = env->GetObjectClass(jStr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

    size_t length = (size_t) env->GetArrayLength(stringJbytes);
    jbyte* pBytes = env->GetByteArrayElements(stringJbytes, nullptr);

    std::string ret = std::string((char *)pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);
    return ret;
}

JNIEXPORT void JNICALL Java_database_DatabaseWrapper_init(JNIEnv *env, jobject obj, jstring str) {
    const char *nativeString = env->GetStringUTFChars(str, nullptr);
        if (nativeString == nullptr) {
            // Handle out of memory or other error
            // Optionally throw an exception or log an error
            return; // Or handle the error gracefully based on your application's logic
        }

        // Clean up existing db if it exists
        if (db) {
            db.reset();
        }

        // Create a new Database object using nativeString
        db = std::make_shared<Database>(nativeString);

        // Release the nativeString memory
        env->ReleaseStringUTFChars(str, nativeString);
}

JNIEXPORT jstring JNICALL Java_database_DatabaseWrapper_getName(JNIEnv *env, jobject obj) {
    return env->NewStringUTF(db->getName().c_str());
}

JNIEXPORT jboolean JNICALL Java_database_DatabaseWrapper_isChanged(JNIEnv *env, jobject obj) {
    return db->isChanged();
}

JNIEXPORT void JNICALL Java_database_DatabaseWrapper_setFilePath(JNIEnv *env, jobject obj, jstring path) {
    const char *nativePath = env->GetStringUTFChars(path, 0);
    db->setFilePath(std::string(nativePath));
    env->ReleaseStringUTFChars(path, nativePath);
}

JNIEXPORT jstring JNICALL Java_database_DatabaseWrapper_getFilePath(JNIEnv *env, jobject obj) {
    return env->NewStringUTF(db->getFilePath()->c_str());
}

JNIEXPORT void JNICALL Java_database_DatabaseWrapper_setChange(JNIEnv *env, jobject obj, jboolean changed) {
    db->setChange(changed);
}

JNIEXPORT void JNICALL Java_database_DatabaseWrapper_executeQuery(JNIEnv *env, jobject obj, jstring queryText) {
    const char *nativeQuery = env->GetStringUTFChars(queryText, 0);
    db->executeQuery(db, std::string(nativeQuery));
    env->ReleaseStringUTFChars(queryText, nativeQuery);
}

JNIEXPORT void JNICALL Java_database_DatabaseWrapper_loadDatabase(JNIEnv *env, jobject obj, jstring path) {
    const char *nativePath = env->GetStringUTFChars(path, nullptr);
    if (nativePath == nullptr) {
        // Handle out of memory or other error
        // Optionally throw an exception or log an error
        return; // Or handle the error gracefully based on your application's logic
    }

    // Call the loadDatabase method and assign the result to db
    db = db->loadDatabase(nativePath);

    // Release the nativePath memory
    env->ReleaseStringUTFChars(path, nativePath);
}
JNIEXPORT jint JNICALL Java_database_DatabaseWrapper_test(JNIEnv *env, jobject obj, jint a, jint b) {
    // Example implementation for test function
    return a + b; // Replace with your actual implementation logic
}
JNIEXPORT void JNICALL Java_database_DatabaseWrapper_exportToSQL(JNIEnv *env, jobject obj, jstring path) {
    std::string exportPath = jstringToString(env, path);
    db->exportToSQL(exportPath);
}

JNIEXPORT void JNICALL Java_database_DatabaseWrapper_exportToCustom(JNIEnv *env, jobject obj, jstring path) {
    std::string exportPath = jstringToString(env, path);
    db->exportToCustom(exportPath);
}