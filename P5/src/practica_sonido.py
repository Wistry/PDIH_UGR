# -*- coding: utf-8 -*-
"""
Script completo para la Práctica 5 (ejercicios 1–6) en Python.
Este script está pensado para ejecutarse en macOS, ya que utiliza el comando 'say' para sintetizar voz.
Las gráficas se guardan como archivos PNG y no se muestran en pantalla.
Parte realizada por Laura Riesco

"""

import subprocess
import numpy as np
import soundfile as sf
import wave
import matplotlib.pyplot as plt
import simpleaudio as sa

# ------------------------------------------------------------
# 1. Generar los archivos WAV con tu nombre y apellido usando 'say'
# ------------------------------------------------------------
def generar_wav_say(texto, nombre_archivo):
    """
    Usa el comando 'say' de macOS para sintetizar 'texto' en un archivo WAV.
    """
    cmd = [
        "say",
        "-o", nombre_archivo,
        "--data-format=LEI16@22050",
        texto
    ]
    subprocess.run(cmd, check=True)
    print(f"✅ Archivo generado: {nombre_archivo} (texto: '{texto}')")

# Permitimos que se puede cambiar el nombre y apellido por los deseados
mi_nombre   = "Carlos"
mi_apellido = "García"

print("Generando archivos de audio con tu nombre y apellido...")
generar_wav_say(mi_nombre,   "nombre.wav")
generar_wav_say(mi_apellido, "apellido.wav")


# ------------------------------------------------------------
# 2. Guardar la forma de onda de cada WAV como imagen PNG
# ------------------------------------------------------------
def plot_waveform_a_png(path_wav, titulo, nombre_png):
    data, fs = sf.read(path_wav)
    if data.ndim == 2:
        data = data.mean(axis=1)
    t = np.linspace(0, len(data)/fs, num=len(data))
    plt.figure(figsize=(8, 3))
    plt.plot(t, data, lw=0.5)
    plt.title(f"Forma de onda: {titulo}  (fs = {fs} Hz)")
    plt.xlabel("Tiempo [s]")
    plt.ylabel("Amplitud")
    plt.tight_layout()
    plt.savefig(nombre_png)
    plt.close()
    print(f"📈 Gráfica guardada en {nombre_png}")

print("Guardando gráficas de las formas de onda...")
plot_waveform_a_png("nombre.wav",   "Nombre",  "nombre_waveform.png")
plot_waveform_a_png("apellido.wav", "Apellido","apellido_waveform.png")


# ------------------------------------------------------------
# 3. Mostrar información de cabecera de los archivos WAV
# ------------------------------------------------------------
def info_header_wave(path_wav):
    with wave.open(path_wav, 'rb') as wf:
        n_channels    = wf.getnchannels()
        fs            = wf.getframerate()
        n_frames      = wf.getnframes()
        sampwidth     = wf.getsampwidth()   # en bytes
        duration_s    = n_frames / fs
        profundidad_b = sampwidth * 8
        print(f"\n== Información de {path_wav} ==")
        print(f" Frecuencia de muestreo: {fs} Hz")
        print(f" Número de canales:       {n_channels}")
        print(f" Profundidad de bits:     {profundidad_b} bits")
        print(f" Número total de frames:  {n_frames}")
        print(f" Duración (s):            {duration_s:.2f}")

print("Mostrando información de los archivos de audio...")
info_header_wave("nombre.wav")
info_header_wave("apellido.wav")


# ------------------------------------------------------------
# 4. Unir ambos sonidos en uno nuevo (“basico.wav”)
# ------------------------------------------------------------
def concatenar_wavs_sf(wav1, wav2, output_wav):
    data1, fs1 = sf.read(wav1)
    data2, fs2 = sf.read(wav2)
    if fs1 != fs2:
        raise ValueError("¡Las frecuencias de muestreo no coinciden!")
    if data1.ndim == 2:
        data1 = data1.mean(axis=1)
    if data2.ndim == 2:
        data2 = data2.mean(axis=1)
    resultado = np.concatenate([data1, data2])
    sf.write(output_wav, resultado, fs1)
    print(f"\n🔗 Concatenado guardado en: {output_wav}  (fs = {fs1} Hz, {len(resultado)} muestras)")

print("Concatenando los dos archivos de audio...")
concatenar_wavs_sf("nombre.wav", "apellido.wav", "basico.wav")


# ------------------------------------------------------------
# 5. Guardar la forma de onda de “basico.wav” y reproducirlo
# ------------------------------------------------------------
print("Guardando gráfica de la forma de onda del archivo concatenado...")
plot_waveform_a_png("basico.wav", "Nombre + Apellido (basico.wav)", "basico_waveform.png")

def reproducir_wav_sf(path_wav):
    data, fs = sf.read(path_wav)
    if data.dtype != np.int16:
        max_val = np.max(np.abs(data))
        if max_val < 1e-8:
            audio_int16 = data.astype(np.int16)
        else:
            audio_int16 = (data / max_val * 32767).astype(np.int16)
    else:
        audio_int16 = data
    num_chan = 1 if audio_int16.ndim == 1 else audio_int16.shape[1]
    play_obj = sa.play_buffer(
        audio_int16,
        num_channels     = num_chan,
        bytes_per_sample = 2,
        sample_rate      = fs
    )
    play_obj.wait_done()

print("\n▶️ Reproduciendo el archivo 'basico.wav'...")
reproducir_wav_sf("basico.wav")


# ------------------------------------------------------------
# 6. Resumen final
# ------------------------------------------------------------
print("\n¡Proceso completado! Tienes los siguientes archivos generados:")
print("  • nombre.wav")
print("  • apellido.wav")
print("  • basico.wav")
print("  • nombre_waveform.png")
print("  • apellido_waveform.png")
print("  • basico_waveform.png")