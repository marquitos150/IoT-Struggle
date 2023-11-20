"use client";
import React, { useState } from "react";
import {useRouter} from 'next/navigation'; 

const page = () => {

    const [macAddress, setMacAddress] = useState("");
    const router = useRouter();

    const registerMAC = async () => {
        router.push("../dashboard");
    };
    
    return (
        <>
            <div className="max-w-5xl w-full h-auto flex justify-between px-4 py-4">
                <div className="h-8"></div>
            </div>
            <div className="w-full max-w-5xl text-black flex flex-col flex-grow items-center py-2 px-8">

                <h1>
                    Register your Trashbin's MAC Address
                </h1>

                <form
                    onSubmit={handleSubmit(registerMAC)}
                    className={`w-full text-base rounded-sm bg-white border-[1px] border-[#C3C3C3] mt-4 shadow-xl p-4 flex flex-col`}
                >
                    <label for="macAddress">
                        MAC Address
                    </label>
                    {errors?.macAddress?.message ? <p className="text-red-400 text-xs">{errors?.macAddress?.message}</p> : <></>}
                    <input
                        {...register("macAddress", { required: "MAC cannot cannot be empty!" })}
                        className="px-2 py-1 mt-1 border-[1px] border-gray-300"
                        type="input"
                        id="macAddress"
                        value={macAddress}
                        onChange={(e) => setMacAddress(e.target.value)}
                    />
                    <button
                        type="submit"
                        id="submit-mac-button"
                        className="focus-within:translate-y-1 transition-all duration-75 rounded-sm font-semibold mt-8 py-1 px-2 text-center border-[2px] border-gray-500 text-gray-500"
                    >
                    </button>
                </form>
            </div>
        </>
    );
}

export default page