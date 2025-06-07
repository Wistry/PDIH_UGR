# -*- coding: utf-8 -*-
"""
Parte extra de la Práctica 5 (ejercicios 7 y 8).
Tras previamente haber generado los archivos WAV con tu nombre y apellido,
este script realiza un filtrado pasa-bajo para eliminar frecuencias de 10.000Hz a 20.000Hz,
y también aplica un efecto de eco y sonido al revés a un archivo de audio.
Parte realizada por William Quinn 
"""

import numpy as np
import soundfile as sf
import scipy.signal
import matplotlib.pyplot as plt

# ------------------------------------------------------------
# 7. Filtro pasa-bajo para eliminar 10.000Hz-20.000Hz
# ------------------------------------------------------------

def filtrar_10K_20K(input_wav, output_wav, max_filter_frequency_hz=10000):
    """
    Aplica un filtro para eliminar las frecuencias superiores a max_filter_frequency_hz, en este caso 10.000Hz.
    Guarda el resultado en un nuevo archivo WAV.
    """
    data, fs = sf.read(input_wav)  # Lee el archivo de audio
    if data.ndim == 2:
        data = data.mean(axis=1)    # Convierte a mono si es estéreo
    # Crea un filtro Butterworth de orden 10
    sos = scipy.signal.butter(10, max_filter_frequency_hz, 'low', fs=fs, output='sos')
    filtrada = scipy.signal.sosfilt(sos, data)  # Aplica el filtro
    sf.write(output_wav, filtrada, fs)          # Guarda el archivo filtrado
    print(f"Archivo filtrado guardado en {output_wav}")

# Aplica el filtro pasa-bajo a 'basico.wav' y guarda el resultado
filtrar_10K_20K("basico.wav", "filtrado.wav")


# ------------------------------------------------------------
# 8. Efecto de eco y sonido al revés
# ------------------------------------------------------------

def aplicar_eco(input_wav, output_wav, delay_ms=300, decay=0.3):
    """
    Aplica un efecto de eco al archivo de entrada y guarda el resultado.
    delay_ms: retardo del eco en milisegundos.
    decay: atenuación del eco, como de fuerte suena, del 0 al 1.
    """
    data, fs = sf.read(input_wav)
    if data.ndim == 2:
        data = data.mean(axis=1)
    delay_samples = int(fs * delay_ms / 1000)  # Calcula el retardo en muestras
    eco = np.zeros(len(data) + delay_samples)  # Crea un array para el eco
    eco[:len(data)] += data                    # Señal original
    eco[delay_samples:] += data * decay        # Señal retardada y atenuada
    eco = eco / np.max(np.abs(eco))            # Normaliza para evitar saturación
    sf.write(output_wav, eco, fs)
    print(f"Archivo con eco guardado en {output_wav}")

def invertir_audio(input_wav, output_wav):
    """
    Invierte el audio (lo reproduce al revés) y guarda el resultado.
    """
    data, fs = sf.read(input_wav)
    if data.ndim == 2:
        data = data.mean(axis=1)
    alreves = data[::-1]           # Invierte la señal
    sf.write(output_wav, alreves, fs)
    print(f"Archivo al revés guardado en {output_wav}")

# Aplica el eco a 'basico.wav' y guarda el resultado en 'eco.wav'
aplicar_eco("basico.wav", "eco.wav")
# Invierte el archivo con eco y guarda el resultado en 'alreves.wav'
invertir_audio("eco.wav", "alreves.wav")

# ------------------------------------------------------------
# Extra: Para comprobar el ejercicio 7 (visualización del espectro)
# ------------------------------------------------------------

def guardar_espectro(input_wav, nombre_png):
    """
    Calcula y guarda el espectro de frecuencias del archivo de audio como imagen PNG.
    Permite visualizar el efecto del filtrado.
    """
    data, fs = sf.read(input_wav)
    if data.ndim == 2:
        data = data.mean(axis=1)
    N = len(data)
    freqs = np.fft.rfftfreq(N, 1/fs)      # Vector de frecuencias
    espectro = np.abs(np.fft.rfft(data))  # Magnitud del espectro
    plt.figure(figsize=(8,3))
    plt.semilogy(freqs, espectro)
    plt.title(f"Espectro de frecuencias de {input_wav}")
    plt.xlabel("Frecuencia (Hz)")
    plt.ylabel("Magnitud")
    plt.tight_layout()
    plt.savefig(nombre_png)
    plt.close()
    print(f"Espectro guardado en {nombre_png}")

# Guarda el espectro antes y después del filtrado para comparar visualmente
guardar_espectro("basico.wav", "espectro_basico.png")
guardar_espectro("filtrado.wav", "espectro_filtrado.png")