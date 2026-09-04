#include <jni.h>
#include <android/log.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/mman.h>

#define TAG "StandoffGodMode"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)

// Функция для записи значений в защищенную память игры
void WriteMemory(uintptr_t address, void* buffer, size_t size) {
    // Снимаем защиту памяти (делаем её доступной для записи)
    mprotect((void*)(address & ~(sysconf(_SC_PAGE_SIZE) - 1)), sysconf(_SC_PAGE_SIZE), PROT_READ | PROT_WRITE | PROT_EXEC);
    // Копируем новые данные по адресу
    memcpy((void*)address, buffer, size);
}

// Карта офсетов для функций
namespace Offsets {
    uintptr_t PlayerManager_TypeInfo = 0x6B53410;[span_0](start_span)[span_0](end_span)
    uintptr_t localPlayerOffset = 0x68;[span_1](start_span)[span_1](end_span)
    uintptr_t spreadOffset = 0x80;[span_2](start_span)[span_2](end_span)
    uintptr_t speedOffset = 0x80;[span_3](start_span)[span_3](end_span)
}

void* main_thread(void*) {
    LOGD("Full working test module loaded!");
    
    uintptr_t libil2cpp = 0;
    while (libil2cpp == 0) {
        libil2cpp = (uintptr_t)dlopen("libil2cpp.so", RTLD_NOLOAD);
        sleep(1);
    }
    
    LOGD("libil2cpp found at: %p", (void*)libil2cpp);

    while (true) {
        // Пример тестовой логики:
        // Когда игрок зайдет в матч, здесь можно вычислять реальный адрес игрока:
        // uintptr_t playerManagerAddr = *(uintptr_t*)(libil2cpp + Offsets::PlayerManager_TypeInfo);
        // if (playerManagerAddr != 0) {
        //      uintptr_t localPlayer = *(uintptr_t*)(playerManagerAddr + Offsets::localPlayerOffset);
        //      if (localPlayer != 0) {
        //           Здесь пишем код изменения значений, например, скорости или здоровья через WriteMemory
        //      }
        // }
        
        sleep(3); // Проверка каждые 3 секунды, чтобы игра не лагала
    }
    
    return NULL;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    pthread_t thread;
    pthread_create(&thread, NULL, main_thread, NULL);
    return JNI_VERSION_1_6;
}
