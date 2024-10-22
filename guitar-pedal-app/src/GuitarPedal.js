import React, { useState, useCallback } from 'react';
import headerImage from 'C:/Users/Geral/Documents/JUCE_tests/CueioDrive/guitar-pedal-app/src/background.png'; // Importe sua imagem do topo aqui

const GuitarPedal = () => {
  const [volume, setVolume] = useState(50);
  const [blend, setBlend] = useState(50);
  const [drive, setDrive] = useState(50);
  const [range, setRange] = useState(50);
  const [effect, setEffect] = useState(false);

  const Knob = ({ value, onChange, color, label }) => {
    const handleWheel = useCallback((e) => {
      e.preventDefault();
      const delta = e.deltaY < 0 ? 1 : -1;
      onChange(prev => Math.min(100, Math.max(0, prev + delta * 2)));
    }, [onChange]);

    const handleMouseDown = useCallback((e) => {
      e.preventDefault();
      const startY = e.clientY;
      const startValue = value;

      const handleMouseMove = (moveEvent) => {
        const deltaY = startY - moveEvent.clientY;
        const deltaValue = Math.round(deltaY / 5);
        onChange(Math.min(100, Math.max(0, startValue + deltaValue)));
      };

      const handleMouseUp = () => {
        document.removeEventListener('mousemove', handleMouseMove);
        document.removeEventListener('mouseup', handleMouseUp);
      };

      document.addEventListener('mousemove', handleMouseMove);
      document.addEventListener('mouseup', handleMouseUp);
    }, [value, onChange]);

    return (
      <div className="flex flex-col items-center">
        <div 
          className={`w-24 h-24 ${color} rounded-full relative cursor-pointer
                      shadow-[inset_0_2px_10px_rgba(0,0,0,0.3),_0_4px_10px_rgba(0,0,0,0.3)]
                      border-4 border-gray-700`}
          onWheel={handleWheel}
          onMouseDown={handleMouseDown}
        >
          <div 
            className="indicator w-2 h-10 bg-gray-200 absolute top-1/2 left-1/2 rounded-full
                       shadow-[0_2px_4px_rgba(0,0,0,0.3)]"
            style={{ transform: `translate(-50%, -50%) rotate(${value * 3.6 - 90}deg) translateY(-40%)` }}
          ></div>
        </div>
        <label className="mt-3 text-gray-300 text-sm font-bold">{label}</label>
        <span className="text-gray-400 text-xs">{value}</span>
      </div>
    );
  };

  return (
    <div className="relative bg-white p-8 rounded-lg shadow-2xl max-w-md mx-auto
                    border-t-4 border-gray-600"
          style={{ height: '600px', paddingTop: '60px' }}> {/* Adiciona espaço para a imagem do cabeçalho */}
      
      {/* Imagem do cabeçalho centralizada */}
      <div className="absolute top-0 left-0 right-0 flex justify-center">
        <img 
          src={headerImage} 
          alt="Header" 
          className="w-64 h-auto" // Ajuste o tamanho conforme necessário
          style={{ maxHeight: '200px', objectFit: 'contain' }} // Limite de altura sem deformar
        />
      </div>

      <div className="grid grid-cols-2 gap-10 mb-8 mt-20"> {/* Adiciona margem acima dos botões */}
        <Knob value={drive} onChange={setDrive} color="bg-gradient-to-br from-red-500 to-red-700" label="DRIVE" />
        <Knob value={range} onChange={setRange} color="bg-gradient-to-br from-red-500 to-red-700" label="RANGE" />
        <Knob value={blend} onChange={setBlend} color="bg-gradient-to-br from-red-500 to-red-700" label="BLEND" />
        <Knob value={volume} onChange={setVolume} color="bg-gradient-to-br from-red-500 to-red-700" label="VOLUME" />
      </div>
      
      {/* Pino metálico com luz acima */}
      <div className="flex justify-center items-center flex-col" style={{ marginTop: '-30px' }}> {/* Ajusta a posição do pino metálico */}
        {/* Luz de "liga-desliga" */}
        <div
          className={`w-4 h-4 rounded-full mb-1 transition-all duration-200
                      ${effect ? 'bg-green-500 shadow-[0_0_10px_rgba(0,255,0,0.7)]' : 'bg-red-500 shadow-[0_0_10px_rgba(255,0,0,0.7)]'}`}
        ></div>

        {/* Pino metálico para ligar/desligar o efeito */}
        <div
          onClick={() => setEffect(!effect)}
          className={`w-12 h-12 rounded-full border-4 ${effect ? 'border-purple-700' : 'border-gray-600'}
                      bg-gray-400 cursor-pointer transition-all duration-200
                      shadow-[0_4px_10px_rgba(0,0,0,0.3)] flex items-center justify-center`}
        >
          <div className={`w-6 h-6 rounded-full ${effect ? 'bg-purple-800' : 'bg-gray-600'} shadow-[0_2px_6px_rgba(0,0,0,0.5)]`}></div>
        </div>
      </div>

      <div className="flex justify-center" style={{ marginTop: '10px' }}> {/* Ajusta a posição do texto para baixo do pino */}
        <span className="text-gray-400 text-xs">Model X-2000</span>
      </div>
    </div>
  );
};

export default GuitarPedal;
